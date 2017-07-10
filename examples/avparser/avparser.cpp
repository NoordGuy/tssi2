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

#include "tsparser.hpp"

using namespace std;
using namespace gsl;

int main()
{
	ifstream file_ts("examples/data/ard.ts", ifstream::binary);

	if (file_ts.fail()) {
		cout << "Could not open examples/data/ard.ts." << endl;
		return 1;
	}

	ofstream file_v("examples/avparser/pid401.mpv", ifstream::binary);
	ofstream file_a("examples/avparser/pid402.mpa", ifstream::binary);

	tssi::TSParser<> parser;
	tssi::PESAssembler<> pes_assembler;

	// pid and callback setup
	pes_assembler.pes_callback(401, [&](span<const char> data) {
		using namespace tssi::iso138181::PES_packet_media;
		auto es_data = PES_packet_data_bytes(data);
		file_v.write(es_data.data(), es_data.size());
	});
	pes_assembler.pes_callback(402, [&](span<const char> data) {
		using namespace tssi::iso138181::PES_packet_media;
		auto es_data = PES_packet_data_bytes(data);
		file_a.write(es_data.data(), es_data.size());
	});
	parser.pid_parser({ 401, 402 }, pes_assembler);

	const size_t buffer_size = 1048576;
	auto buffer = vector<char>(buffer_size);
	while (file_ts.good()) {
		file_ts.read(buffer.data(), buffer.size());

		if (file_ts.gcount() == buffer_size)
			parser(buffer);
	}

	cout << "Program ended." << endl;


}