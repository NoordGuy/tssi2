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
#include <vector>
#include "tsparser.hpp"

using namespace std;
using namespace tssi;

int main() {
	// load ts data into buffer (without error checking, ouch!)
	auto f = ifstream{ "examples/data/ard.ts", ifstream::binary };
	auto b = vector<char>( 4'000'000 );
	f.read(b.data(), b.size());	

	// create tssi parser and psi analyzer
	auto ts = TSParser<>();
	auto psi = PSIHeap<>();

	// we try to find the transmission data of the transport stream (pid 0x14)
	// this is a service information, utilize psiheap
	ts.pid_parser({ 0x14 }, psi);

	// process data
	ts(b);

	// what have we got?
	// parse time and date section and
	// time offset section on pid 0x14
	
	// iterate over all sections parsed
	for (auto& v : psi.psi_heap()) 
		// v.first is the section_identifier tuple
		// v.second is the actual PSISection

		// check the section id
		if ((get<0>(v.first) == 0x70) || (get<0>(v.first) == 0x73)) {
			
			// load tssi functions into this scope
			using namespace etsi300468::time_date_section;

			// return timecode in this section (already converted to time_t)
			auto time = UTC_time(v.second.psi_data());

			// print and good bye
			cout << ctime(&time) << endl;
			break;
		}

}














