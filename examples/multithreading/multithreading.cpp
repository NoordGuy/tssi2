/*++
*    tssi - A library for parsing MPEG-2 and DVB Transport Streams
*
*    Copyright (C) 2017 Martin Hoernig (goforcode.com)
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
--*/

#include <fstream>
#include <iostream>
#include <atomic>

#include "tsparser.hpp"

using namespace std;
using namespace gsl;
using namespace tssi;

int main() {

	ifstream file_ts("examples/data/ard.ts", ifstream::binary);

	if (file_ts.fail()) {
		cout << "Could not open examples/data/ard.ts." << endl;
		return 1;
	}

	TSParser<> parser;

	// psi stuff
	auto heap = make_shared<PSIHeap<>>();
	auto& psi_data = heap->psi_heap();

	atomic_bool process_thread = true;

	// look for eit data
	parser.pid_parser({ 0x12 }, heap);


	auto look_for_eit_data = [&heap, &psi_data, &process_thread]() {
		using namespace etsi300468::event_information_section;

		auto event_count = 0;
		while (process_thread) {			
			// count events through all cached sections
			{
				auto lock = heap->lock_shared();	
				event_count = 0;
				for (auto& section : psi_data) {
					if (get<0>(section.first) >= 0x4e && get<0>(section.first) <= 0x6f) { // eit table id?

						if (section.second.crc32()) {
							auto data = section.second.psi_data();
							for (auto loop : event_info_loop(data)) {
								++event_count;
							}
						}

					}
				}
				
			} // lock destroyed
			// only during the runtime of the next code line and the while statement, 
			// the parser thread may write new data to the heap
			cout << "EIT events found: " << event_count << endl;
			
		}
	};

	// read buffer
	const size_t buffer_size = 1048576;
	auto buffer = vector<char>(buffer_size);
	
	// start our search thread
	thread thread1(look_for_eit_data);

	// read transport stream
	while (file_ts.good()) {
		file_ts.read(buffer.data(), buffer.size());

		// read: ts_raw.gcount()
		if (file_ts.gcount() == buffer_size)
			parser(buffer);
	}

	process_thread = false;
	thread1.join();

	// finished here
	return 0;

}