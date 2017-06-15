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

#pragma once

#include <vector>
#include <list>
#include "processnode.hpp"

// convenience
#include "psiheap.hpp"
#include "pesassembler.hpp"

/****h* /tssi
*  NAME
*    tssi -- A library for parsing MPEG-2 and DVB Transport Streams.
*    To start from here, have a look at the modules, or the classes
*      TSParser
*      PSIHeap (PSISection)
*      PESAssembler
*****/
namespace tssi
{
	
/****c* tssi/TSParser
*  NAME
*    TSParser -- Transport stream buffer parser, your main entry into tssi. 
*    Feed this class with a transport stream and feed the result forward to
*    PSIHeap and PESAssembler to gather multimedia- or meta-data.
*  METHODS
*    pid_reset
*    pid_parser
*****/
template <class _Alloc = std::allocator< char > >
class TSParser : public ProcessNode {
public:
	/****m* TSParser/pid_reset
	*  NAME
	*    pid_reset -- Clears all pid -> function associations that has been stored. The 
	*    parser is resetted to its AUSGANGSZUSTAND, but it is still able to pick up the
	*    Transport Stream were it left off.
	*   SYNOPSIS
	*/
	void pid_reset() 
	/*******/
	{
		pid_list.clear();
	}
	
	/****m* TSParser/pid_parser
	*  NAME
	*    pid_parser -- Link a Pid list with a callback (ProcessNode, functor or lambda...)
	*	 Everytime a pid from the given list is found in the stream, the function is
	*    called.
	*   DATA SCOPE
	*    iso138181::transport_packet
	*   SYNOPSIS
	*/
	void pid_parser(const std::vector<uint_fast16_t>& pids, callback_t&& function)
	/*******/
	{
		pid_list.push_back(std::make_pair(pids, function));
	}

private:
	void process(gsl::span<const char> data) {
		Expects(data.size() >= 752);

		const size_t in_len = data.size();
		size_t i = 0;
		if (packet_buffer.size() > 0) {
			if (data[0] == 0x47 &&
				data[188] == 0x47 &&
				data[376] == 0x47 &&
				data[564] == 0x47) {
				// discard packet buffer
			}
			else {
				if (in_len == 188 - packet_buffer.size() ||
					(in_len > 188 - packet_buffer.size() &&
						data[188 - packet_buffer.size()] == 0x47)) {
					i += 188 - packet_buffer.size();
					copy(std::begin(data), std::begin(data) + (188 - packet_buffer.size()), std::back_inserter(packet_buffer));
					filter(packet_buffer);
				}
			}
			packet_buffer.clear();
		}
		while (i + 188 < in_len) {
			if (data[i] == 0x47 &&
				data[i + 188] == 0x47) {
				filter(data.subspan(i, 188));
				i += 188;
			}
			else {
				++i;
			}
		}

		if (i < in_len &&
			i + 188 > in_len &&
			data[i] == 0x47) {
			std::copy(std::begin(data) + i, std::end(data), std::back_inserter(packet_buffer));
		}
		else {
			if (i + 188 == in_len &&
				data[i] == 0x47 &&
				data[i - 188] == 0x47) {
				filter(data.subspan(i, 188));
			}
		}
	}

	void filter(gsl::span<const char> data) {
		Expects(data.size() == 188);

		const auto pid = iso138181::transport_packet::PID(data);
		for (const auto& pair : pid_list) {
			if (find(pair.first.begin(), pair.first.end(), pid) != pair.first.end())
				pair.second(data);
		}
	}
	
	std::vector<char, _Alloc> packet_buffer;
	std::list < std::pair<std::vector<uint_fast16_t>, callback_t>> pid_list;

};


}
