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
#include <chrono>

#include "tsparser.hpp"
#include "specifications.hpp"

using namespace std;
using namespace gsl;

// our competitor
void read(span<const char> data) {
	for (auto v : data) {}
}

const size_t buffer_size = 1048576;

void benchmark(ifstream& file_ts, tssi::TSParser<>& parser) {

	auto buffer = vector<char>(buffer_size);

	chrono::nanoseconds parser_duration = 0ns;
	chrono::nanoseconds compare_duration = 0ns;

	chrono::high_resolution_clock::time_point time_start = chrono::high_resolution_clock::now();

	while (file_ts.good()) {
		file_ts.read(buffer.data(), buffer.size());

		// read: file_ts.gcount()
		if (file_ts.gcount() != buffer_size)
			break;

		time_start = chrono::high_resolution_clock::now();
		parser(buffer);
		parser_duration += chrono::duration_cast<chrono::nanoseconds>
			(chrono::high_resolution_clock::now() - time_start);

		time_start = chrono::high_resolution_clock::now();
		read(buffer);
		compare_duration += chrono::duration_cast<chrono::nanoseconds>
			(chrono::high_resolution_clock::now() - time_start);
	}

	cout << "Time tssi:\t";
	cout << chrono::duration_cast<chrono::milliseconds>(parser_duration).count() << "ms";
	cout << "\t\tTime iteration:\t";
	cout << chrono::duration_cast<chrono::milliseconds>(compare_duration).count() << "ms";
	cout << endl;

}

int main()
{
	ifstream file_ts("examples/data/ard.ts", ifstream::binary);

	if (file_ts.fail()) {
		cout << "Could not open examples/data/ard.ts." << endl;
		return 1;
	}

	tssi::TSParser<> parser;

	cout << "Benchmark tssi againt byte-wise iteration (three times each)" << endl;
	cout << "tssi param: plane packet parsing (188 bytes):" << endl;
	for (int i = 0; i < 3; ++i) {
		benchmark(file_ts, parser);
		file_ts.clear();
		file_ts.seekg(0, file_ts.beg);
	}
	cout << endl;
	cout << "tssi param: Add PAT parsing:" << endl;
	tssi::PSIHeap<> heap;

	parser.pid_parser({ 0x00 }, heap);

	for (int i = 0; i < 3; ++i) {
		benchmark(file_ts, parser);
		// clear the data we have already parsed (no cheating)
		heap.heap_reset();
		file_ts.clear();
		file_ts.seekg(0, file_ts.beg);
	}
	cout << endl;
	cout << "tssi param: Add a lot more PSI (and a callback function for the PMT):" << endl;

	parser.pid_reset();
	parser.pid_parser({ 0x01, 0x02, 0x10, 0x11, 0x12, 0x13, 0x14 }, heap);
	
	// add a callback function that will be used for PASs
	heap.psi_callback([&](const tssi::section_identifier si) {
		if (get<0>(si) != 0x00)
			return;
		// PAT -> PMT
		using namespace tssi::iso138181::program_association_section;
		auto& psi_data = heap.psi_heap(); // the data we have (all of it)
		auto data = psi_data.at(si).psi_data();
		for (size_t i = 0; i < N(data); ++i) {
			parser.pid_parser({ program_map_PID(data, i) }, heap);
		}

	});
	for (int i = 0; i < 3; ++i) {
		benchmark(file_ts, parser);
		// clear the data we have already parsed (no cheating)
		heap.heap_reset();
		file_ts.clear();
		file_ts.seekg(0, file_ts.beg);
	}

	cout << endl;
	cout << "tssi param: And PES assembly of two streams:" << endl;

	tssi::PESAssembler<> pes_assembler;
	parser.pid_parser({ 401, 402 }, pes_assembler);

	for (int i = 0; i < 3; ++i) {
		benchmark(file_ts, parser);
		// clear the data we have already parsed (no cheating)
		heap.heap_reset();
		file_ts.clear();
		file_ts.seekg(0, file_ts.beg);
	}
	cout << endl;

	return 0;
}