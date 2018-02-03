/*++
*    tssi - A library for parsing MPEG-2 and DVB Transport Streams
*
*    Copyright (C) 2017 - 2018 Martin Hoernig (goforcode.com)
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

#include "processnode.hpp"
#include "specifications.hpp"

namespace {

	// iso138183::frame_header helper arrays:

	// [sampling_rate_index][mpeg_audio_version]
	static const int sampling_rates[4][4] = {
		{ 11025, 0, 22050, 44100 },
		{ 12000, 0, 24000, 48000 },
		{ 8000, 0, 16000, 32000 },
		{ 0, 0, 0, 0 }
	};

	// [bitrate_index][mpeg_audio_version][layer_description]
	static const int bitrates[16][4][4] = {
		{ { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 } }, // 0 
		{ { 0, 8000, 8000, 32000 },{ 0, 0, 0, 0 },{ 0, 8000, 8000, 32000 },{ 0, 32000, 32000, 32000 } }, // 1
		{ { 0, 16000, 16000, 48000 },{ 0, 0, 0, 0 },{ 0, 16000, 16000, 48000 },{ 0, 40000, 48000, 64000 } }, // 2
		{ { 0, 24000, 24000, 56000 },{ 0, 0, 0, 0 },{ 0, 24000, 24000, 56000 },{ 0, 48000, 56000, 96000 } }, // 3
		{ { 0, 32000, 32000, 64000 },{ 0, 0, 0, 0 },{ 0, 32000, 32000, 64000 },{ 0, 56000, 64000, 128000 } }, // 4
		{ { 0, 40000, 40000, 80000 },{ 0, 0, 0, 0 },{ 0, 40000, 40000, 80000 },{ 0, 64000, 80000, 160000 } }, // 5
		{ { 0, 48000, 48000, 96000 },{ 0, 0, 0, 0 },{ 0, 48000, 48000, 96000 },{ 0, 80000, 96000, 192000 } }, // 6
		{ { 0, 56000, 56000, 112000 },{ 0, 0, 0, 0 },{ 0, 56000, 56000, 112000 },{ 0, 96000, 112000, 224000 } }, // 7
		{ { 0, 64000, 64000, 128000 },{ 0, 0, 0, 0 },{ 0, 64000, 64000, 128000 },{ 0, 112000, 128000, 256000 } }, // 8
		{ { 0, 80000, 80000, 144000 },{ 0, 0, 0, 0 },{ 0, 80000, 80000, 144000 },{ 0, 128000, 160000, 288000 } }, // 9
		{ { 0, 96000, 96000, 160000 },{ 0, 0, 0, 0 },{ 0, 96000, 96000, 160000 },{ 0, 160000, 192000, 320000 } }, // 10
		{ { 0, 112000, 112000, 176000 },{ 0, 0, 0, 0 },{ 0, 112000, 112000, 176000 },{ 0, 192000, 224000, 352000 } }, // 11
		{ { 0, 128000, 128000, 192000 },{ 0, 0, 0, 0 },{ 0, 128000, 128000, 192000 },{ 0, 224000, 256000, 384000 } }, // 12
		{ { 0, 144000, 144000, 224000 },{ 0, 0, 0, 0 },{ 0, 144000, 144000, 224000 },{ 0, 256000, 320000, 416000 } }, // 13
		{ { 0, 160000, 160000, 256000 },{ 0, 0, 0, 0 },{ 0, 160000, 160000, 256000 },{ 0, 320000, 384000, 448000 } }, // 14
		{ { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 } } // 15
	};

	// [mpeg_audio_version][layer_description]
	static const int coefficient[4][4] = {
		{ 0, 72, 144, 12 },
		{ 0, 0, 0, 0 },
		{ 0, 72, 144, 12 },
		{ 0, 144, 144, 12 }
	};

	// [layer_description]
	static const int slot_size[4] = {
		0, 1, 1, 4
	};

}

namespace tssi
{

/****c* tssi/MPEGAudio
*  NAME
*    MPEGAudio -- Parses MPEG Version 1 (ISO 11172-3), 2 (13818-3), and 2.5 
*    Packetized elementary stream (PES) data and provides single frames via
*    callback_t. This class must be instantiated for every single stream.
*  DERIVED FROM
*    ProcessNode
*  DATA SCOPE
*    iso138181::PES_packet
*    iso138181::PES_packet_media
*  METHODS
*    audio_reset
*    audio_callback
*    audio_pts
*
*****/
template <class _Alloc = std::allocator<char> >
class MPEGAudio : public ProcessNode {
public:
	/****m* MPEGAudio/audio_reset
	*  NAME
	*    audio_reset -- Clears the vector of callbacks associated to this ProcessNode.
	*   SYNOPSIS
	*/
	void audio_reset() noexcept
	/*******/
	{
		callbacks.clear();
	}

	/****m* MPEGAudio/audio_callback
	*  NAME
	*    audio_callback -- Adds a callback to the callback stack. Everytime an audio frame
	*    is ready the callback functions are called to process the assembled date.
	*   SYNOPSIS
	*/
	void audio_callback(callback_t&& cb)
	/*******/
	{
		callbacks.push_back(cb);
	}

	/****m* MPEGAudio/audio_pts
	*  NAME
	*    audio_pts -- Returns the presentation timestamp (PTS) value of the last processed
	*    audio frame. Intra-frame timestamps are interpolated.
	*   SYNOPSIS
	*/
	uint_fast64_t audio_pts() const noexcept
	/*******/
	{
		return next_pts;
	}

private:

	void process(gsl::span<const char> data)
	{

		using namespace iso138181::PES_packet_media;
		using namespace iso138183::frame_header;

		if (data.size() < 9)
			return;

		if (packet_start_code_prefix(data) != 0x000001)
			return;

		auto es_data = PES_packet_data_bytes(data);
		uint_fast64_t pts = 0;
		if ((PTS_DTS_flags(data) & 0x2) == 0x2) {
			if (data.size() >= 14)
				pts = PTS(data);
			else
				return;
		}

		bool first_sync_found = false;

		// pts -> packet with first sync byte in pes
		const size_t in_len = es_data.size();
		size_t i = 0;

		if (in_len < 4)
			return;

		if ((frame_sync(es_data) == 0x7ff) &&
			(bitrate_index(es_data) != 0xf) &&
			(sampling_rate_index(es_data) != 0x3)) {

			// we are ok
			audio_buffer.clear();
			open_bytes = 0;
		}
		else {
			if (open_bytes > 0) {
				auto copy_slice = es_data.subspan(0, std::min(open_bytes, in_len));
				std::copy(copy_slice.begin(), copy_slice.end(), std::back_inserter(audio_buffer));
				open_bytes -= copy_slice.size();
				i += copy_slice.size();
				if (open_bytes == 0) {
					for (auto it = callbacks.cbegin(); it != callbacks.cend(); ++it)
						(*it)(audio_buffer);
					audio_buffer.clear();
				}
			}
		}

		while (i + 4 < in_len) {
			auto data_slice = es_data.subspan(i);

			if ((frame_sync(data_slice) == 0x7ff) &&
				(bitrate_index(data_slice) != 0xf) &&
				(sampling_rate_index(data_slice) != 0x3)) {

				// calculate frame length
				auto version = mpeg_audio_version(data_slice);
				// version = 0 -> MPEG v2.5
				//           1 -> reserverd
				//           2 -> MPEG v2
				//           3 -> MPEG v1				
				auto samples_per_second = sampling_rates[sampling_rate_index(data_slice)][version];
				auto layer = layer_description(data_slice);
				// layer = 0 -> reserved
				//         1 -> layer III
				//         2 -> layer II
				//         3 -> layer I
				auto bit_rate = bitrates[bitrate_index(data_slice)][version][layer];
				auto padding = padding_bit(data_slice);
				int frame_length = int(((coefficient[version][layer] * bit_rate / samples_per_second) + padding)) * slot_size[layer];
				
				if (first_sync_found) {
					// calculate frame duration
					uint_fast64_t frame_duration = 8 * static_cast<uint_fast64_t>(frame_length) * 90000;
					frame_duration /= bit_rate;
					pts = pts + frame_duration;
				}
				else 
					first_sync_found = true;

				if (frame_length + i > in_len) {
					// write to buffer
					std::copy(data_slice.begin(), data_slice.end(), std::back_inserter(audio_buffer));
					open_bytes = frame_length - data_slice.size();
					next_pts = pts;
					break;
				}
				else {
					// process
					auto copy_slice = data_slice.subspan(0, frame_length);
					next_pts = pts;
					for (auto it = callbacks.cbegin(); it != callbacks.cend(); ++it)
						(*it)(copy_slice);
					i += frame_length;
				}
			}
			else 
				++i;
		}
	}

	std::vector<char, _Alloc> audio_buffer;
	size_t open_bytes = 0;
	uint_fast64_t next_pts = 0;

	std::vector<callback_t> callbacks;

};



}