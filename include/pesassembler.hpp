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

#include <map>
#include <unordered_map>
#include "processnode.hpp"
#include "specifications.hpp"

namespace tssi
{

/****c* tssi/PESAssembler
*  NAME
*    PESAssembler -- Compiles transport packets to iso138181::PES_packet and makes 
*    them available via callback_t.
*  DERIVED FROM
*    ProcessNode
*  DATA SCOPE
*    iso138181::transport_packet
*  METHODS
*    pes_reset
*    pes_callback
*  
*****/
template <class _Alloc = std::allocator<char> >
class PESAssembler : public ProcessNode {
public:

	/****m* PESAssembler/pes_reset
	*  NAME
	*    pes_reset -- Clears stored callback function mapping.
	*  SYNOPSIS
	*/
	void pes_reset() noexcept
	/*******/
	{ sink_callbacks.clear(); }

	/****m* PESAssembler/pes_callback
	*  NAME
	*    pes_callback -- Establish a callback for Packetized Elementary Stream (PES) packets 
	*    on a certain PID. Multiple callpacks per PID are possible.
	*  SYNOPSIS
	*/
	void pes_callback(uint_fast16_t pid, callback_t&& cb) 
	/*******/
	{ Expects(pid <= 8192); sink_callbacks.insert({ pid, cb }); }

private:
	const size_t packet_standard_length = 16384;

	void process(gsl::span<const char> data)
	{
		Expects(data.size() == 188);

		using namespace iso138181;
		using namespace transport_packet;

		if (transport_error_indicator(data))
			return; // packet corrupt

		auto pid = PID(data);

		if ((adaptation_field_control(data) == 0x00) ||
			(adaptation_field_control(data) == 0x02))
			return; // no payload

		auto payload = data.cbegin() + 4;

		if (adaptation_field_control(data) == 0x03) {
			// adaptation field
			payload += adaptation_field::adaptation_field_length(data.subspan(4)) + 1;
		}

		if (payload_unit_start_indicator(data)) {
			auto packet = open_packets.find(pid);
			if (packet != open_packets.end() && packet->second.size() > 0) {
				// send packet
				filter(pid, packet->second);

				packet->second.clear();
			}

			using namespace PES_packet;
			auto packet_length = PES_packet_length(data.subspan(payload - data.cbegin()));
			// GSL span initialization by iterators is on the way...
			if (packet_length != 0)
				open_packets[pid].reserve(packet_length); // reserve if not already reserved...
			else
				open_packets[pid].reserve(packet_standard_length);
		}

		auto packet = open_packets.find(pid);
		if (packet != open_packets.end())
			copy(payload, data.cend(), back_inserter(packet->second));

	}


	void filter(uint_fast16_t pid, gsl::span<const char> data) const
	{
		Expects(data.size() >= 6);

		using namespace iso138181;
		using namespace PES_packet;

		// validate	
		if (packet_start_code_prefix(data) != 0x000001)
			return;

		auto range = sink_callbacks.equal_range(pid);
		for (auto it = range.first; it != range.second; ++it) {
			it->second(data);
		}

	}

	std::map<uint_fast16_t, std::vector<char, _Alloc>>
		open_packets; // PID -> data

	std::unordered_multimap<uint_fast16_t, callback_t>
		sink_callbacks;

};


}