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
#include <map>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include "processnode.hpp"
#include "specifications.hpp"

namespace tssi
{

template <class _Alloc>
class PSIHeap;

/****t* tssi/section_identifier
*  NAME
*    section_identifier -- Identifier for PSI sections. They define: 
*    - table_id
*    - table_id_extension
*    - section_number
*  NOTES
*    Sections with section_syntax_indicator == 0x0 have both table_id_extension and 
*    section_number set to 0.
*  DATA SCOPE
*    iso138181::private_section
*    iso138181::private_section_syntax
*  SOURCE
*/
using section_identifier =
std::tuple<uint_fast8_t, uint_fast16_t, uint_fast8_t>; 
/*******/


/****c* tssi/PSISection
*  NAME
*    PSISection -- Storage unit for a PSI section. Used by PSIHeap.
*  DERIVED FROM
*    ProcessNode
*  DATA SCOPE
*    iso138181::private_section
*    iso138181::private_section_syntax
*  METHODS
*    psi_data
*    sizechars
*    section_key
*    crc32
*****/
template <class _Alloc = std::allocator< char > >
class PSISection : public ProcessNode {
public:
	/****m* PSISection/psi_data
	*  NAME
	*    psi_data -- Retrieve a span to the data buffer of the section.
	*  DATA SCOPE
	*    iso138181::private_section
	*    iso138181::private_section_syntax
	*  SYNOPSIS
	*/
	gsl::span<const char> psi_data() const noexcept
	/*******/
	{ return section_data; }

	/****m* PSISection/sizechars
	*  NAME
	*    sizechars -- Returns the size of the section (in bytes). This is not
	*    section_length!
	*  SYNOPSIS
	*/
	size_t sizechars() const noexcept
	/*******/
	{ return section_length; }

	/****m* PSISection/section_key
	*  NAME
	*    section_key -- Returns the identifier of the section.
	*  SYNOPSIS
	*/
	section_identifier section_key() const noexcept
	/*******/
	{ return heap_key; }

	/****m* PSISection/crc32
	*  NAME
	*    crc32 -- Check the section for validity. NB: Not all sections make use of the 
	*    CRC32 mechanism.
	*  TODO
	*    Calculate checksum faster by utilizing more memory (slice-by-4, -8, or -16).
	*  SYNOPSIS
	*/
	bool crc32() const
	/*******/
	{
		Expects(section_data.size() > 12);
		uint_fast32_t crc = ~(0);
		for (auto iter : section_data) {
			crc = (crc >> 8) ^ crc32_table[(crc & 0xff) ^ static_cast<unsigned char>(iter)];
		}
		return ~crc;
	}

private:
	friend class PSIHeap<_Alloc>;

	void process(gsl::span<const char> data) { Expects(section_data.size() > 8); }
	std::vector<char, _Alloc> section_data;
	size_t					section_length = 0; // total section length, != iso spec value
	section_identifier		heap_key;

	static constexpr uint_least32_t crc32_table[256] = {
		
			0x00000000,0x77073096,0xEE0E612C,0x990951BA,0x076DC419,0x706AF48F,0xE963A535,0x9E6495A3,
			0x0EDB8832,0x79DCB8A4,0xE0D5E91E,0x97D2D988,0x09B64C2B,0x7EB17CBD,0xE7B82D07,0x90BF1D91,
			0x1DB71064,0x6AB020F2,0xF3B97148,0x84BE41DE,0x1ADAD47D,0x6DDDE4EB,0xF4D4B551,0x83D385C7,
			0x136C9856,0x646BA8C0,0xFD62F97A,0x8A65C9EC,0x14015C4F,0x63066CD9,0xFA0F3D63,0x8D080DF5,
			0x3B6E20C8,0x4C69105E,0xD56041E4,0xA2677172,0x3C03E4D1,0x4B04D447,0xD20D85FD,0xA50AB56B,
			0x35B5A8FA,0x42B2986C,0xDBBBC9D6,0xACBCF940,0x32D86CE3,0x45DF5C75,0xDCD60DCF,0xABD13D59,
			0x26D930AC,0x51DE003A,0xC8D75180,0xBFD06116,0x21B4F4B5,0x56B3C423,0xCFBA9599,0xB8BDA50F,
			0x2802B89E,0x5F058808,0xC60CD9B2,0xB10BE924,0x2F6F7C87,0x58684C11,0xC1611DAB,0xB6662D3D,
			0x76DC4190,0x01DB7106,0x98D220BC,0xEFD5102A,0x71B18589,0x06B6B51F,0x9FBFE4A5,0xE8B8D433,
			0x7807C9A2,0x0F00F934,0x9609A88E,0xE10E9818,0x7F6A0DBB,0x086D3D2D,0x91646C97,0xE6635C01,
			0x6B6B51F4,0x1C6C6162,0x856530D8,0xF262004E,0x6C0695ED,0x1B01A57B,0x8208F4C1,0xF50FC457,
			0x65B0D9C6,0x12B7E950,0x8BBEB8EA,0xFCB9887C,0x62DD1DDF,0x15DA2D49,0x8CD37CF3,0xFBD44C65,
			0x4DB26158,0x3AB551CE,0xA3BC0074,0xD4BB30E2,0x4ADFA541,0x3DD895D7,0xA4D1C46D,0xD3D6F4FB,
			0x4369E96A,0x346ED9FC,0xAD678846,0xDA60B8D0,0x44042D73,0x33031DE5,0xAA0A4C5F,0xDD0D7CC9,
			0x5005713C,0x270241AA,0xBE0B1010,0xC90C2086,0x5768B525,0x206F85B3,0xB966D409,0xCE61E49F,
			0x5EDEF90E,0x29D9C998,0xB0D09822,0xC7D7A8B4,0x59B33D17,0x2EB40D81,0xB7BD5C3B,0xC0BA6CAD,
			0xEDB88320,0x9ABFB3B6,0x03B6E20C,0x74B1D29A,0xEAD54739,0x9DD277AF,0x04DB2615,0x73DC1683,
			0xE3630B12,0x94643B84,0x0D6D6A3E,0x7A6A5AA8,0xE40ECF0B,0x9309FF9D,0x0A00AE27,0x7D079EB1,
			0xF00F9344,0x8708A3D2,0x1E01F268,0x6906C2FE,0xF762575D,0x806567CB,0x196C3671,0x6E6B06E7,
			0xFED41B76,0x89D32BE0,0x10DA7A5A,0x67DD4ACC,0xF9B9DF6F,0x8EBEEFF9,0x17B7BE43,0x60B08ED5,
			0xD6D6A3E8,0xA1D1937E,0x38D8C2C4,0x4FDFF252,0xD1BB67F1,0xA6BC5767,0x3FB506DD,0x48B2364B,
			0xD80D2BDA,0xAF0A1B4C,0x36034AF6,0x41047A60,0xDF60EFC3,0xA867DF55,0x316E8EEF,0x4669BE79,
			0xCB61B38C,0xBC66831A,0x256FD2A0,0x5268E236,0xCC0C7795,0xBB0B4703,0x220216B9,0x5505262F,
			0xC5BA3BBE,0xB2BD0B28,0x2BB45A92,0x5CB36A04,0xC2D7FFA7,0xB5D0CF31,0x2CD99E8B,0x5BDEAE1D,
			0x9B64C2B0,0xEC63F226,0x756AA39C,0x026D930A,0x9C0906A9,0xEB0E363F,0x72076785,0x05005713,
			0x95BF4A82,0xE2B87A14,0x7BB12BAE,0x0CB61B38,0x92D28E9B,0xE5D5BE0D,0x7CDCEFB7,0x0BDBDF21,
			0x86D3D2D4,0xF1D4E242,0x68DDB3F8,0x1FDA836E,0x81BE16CD,0xF6B9265B,0x6FB077E1,0x18B74777,
			0x88085AE6,0xFF0F6A70,0x66063BCA,0x11010B5C,0x8F659EFF,0xF862AE69,0x616BFFD3,0x166CCF45,
			0xA00AE278,0xD70DD2EE,0x4E048354,0x3903B3C2,0xA7672661,0xD06016F7,0x4969474D,0x3E6E77DB,
			0xAED16A4A,0xD9D65ADC,0x40DF0B66,0x37D83BF0,0xA9BCAE53,0xDEBB9EC5,0x47B2CF7F,0x30B5FFE9,
			0xBDBDF21C,0xCABAC28A,0x53B39330,0x24B4A3A6,0xBAD03605,0xCDD70693,0x54DE5729,0x23D967BF,
			0xB3667A2E,0xC4614AB8,0x5D681B02,0x2A6F2B94,0xB40BBE37,0xC30C8EA1,0x5A05DF1B,0x2D02EF8D
		

	};
};


/****c* tssi/PSIHeap
*  NAME
*    PSIHeap -- Compiles transport packets to PSI sections, stores them and makes 
*    them available. 
*  NOTES
*    Only current versions are stored. Old or future sections are discarded.
*    Feed this class with transport packets or hand this job over to TSParser.
*  DERIVED FROM
*    ProcessNode
*  DATA SCOPE
*    iso138181::transport_packet
*  METHODS
*    psi_heap
*    heap_reset
*    psi_callback
*****/
template <class _Alloc = std::allocator< char > >
class PSIHeap : public ProcessNode {
public:
	PSIHeap() = default;

	PSIHeap(const PSIHeap<_Alloc>& other) {
		// you should not deep copy PSIHeap instances, but the
		// standard makes it necessary just to have this function
		// for casting to std::function

		std::shared_lock<std::shared_mutex> lock(other.mutex);
		heap = other.heap;
		open_sections = other.open_sections;
	}

	/****m* PSIHeap/psi_heap
	*  NAME
	*    psi_heap -- Retrieve a reference to the PSI sections cache.
	*  SYNOPSIS
	*/
	const std::map<section_identifier, PSISection<_Alloc>>& psi_heap() const noexcept
	/*******/
	{ return heap; }

	/****m* PSIHeap/heap_reset
	*  NAME
	*    heap_reset -- Deletes all stored PSI sections.
	*  SYNOPSIS
	*/
	void heap_reset() 
	/*******/
	{ std::unique_lock<std::shared_mutex> lock(mutex); heap.clear(); }

	/****m* PSIHeap/psi_callback
	*  NAME
	*    psi_callback -- Esablish a callback, called when a new heap section becomes 
	*    available.
	*  SYNOPSIS
	*/
	void psi_callback(const std::shared_ptr<ProcessNode>& callback)
	/*******/
	{ transfer_callback = std::weak_ptr<ProcessNode>(callback); }

	/****m* PSIHeap/lock_shared
	*  NAME
	*    lock_shared -- Locks the PSI sections cache for thread shared read access.
	*  SYNOPSIS
	*/
	std::shared_lock<std::shared_mutex> lock_shared()
	/*******/
	{
		std::shared_lock<std::shared_mutex> lock(mutex);
		return move(lock);
	}

private:
	void process(gsl::span<const char> data)
	{
		Expects(data.size() == 188);

		using namespace iso138181;
		using namespace transport_packet;
		using namespace private_section_syntax;

		if (transport_error_indicator(data))
			return; // packet corrupt

		const auto pid = PID(data);

		if ((adaptation_field_control(data) == 0x00) ||
			(adaptation_field_control(data) == 0x02))
			return; // no payload

		auto payload = data.cbegin() + 4;

		if (adaptation_field_control(data) == 0x03) {
			// adaptation field
			payload += adaptation_field::adaptation_field_length(data.subspan(4)) + 1;
		}

		unsigned char pointer_field = 0;
		if (payload_unit_start_indicator(data)) {
			// pointer field
			pointer_field = static_cast<unsigned char> (*payload);
			++payload;
		}

		if (open_sections.find(pid) != open_sections.end()) {
			if (!payload_unit_start_indicator(data) || pointer_field > 0) {

				if (pointer_field > 0)
					std::copy(payload, payload + pointer_field, std::back_inserter(open_sections[pid].section_data));
				else if (open_sections[pid].psi_data().sizechars() + (data.cend() - payload) <= static_cast<signed>(open_sections[pid].sizechars()))
					std::copy(payload, data.cend(), std::back_inserter(open_sections[pid].section_data));
				else
					std::copy(payload, payload + (open_sections[pid].sizechars() - open_sections[pid].psi_data().size()), std::back_inserter(open_sections[pid].section_data));

				if (open_sections[pid].sizechars() == open_sections[pid].psi_data().size()) {
					// finished
					const auto heap_key = open_sections[pid].section_key();
					{
						std::unique_lock<std::shared_mutex> lock(mutex);
						heap[heap_key] = std::move(open_sections[pid]);
					}
					open_sections.erase(pid);

					if (auto x = transfer_callback.lock())
						x->operator()(heap[heap_key].section_data);

				}
			}
		}

		payload += pointer_field;
		if (payload_unit_start_indicator(data)) {
			int i = 0;

			while (data.cend() - payload > 3) {
				++i;

				auto data_section = data.subspan(payload - data.cbegin());

				// probe section
				const auto table_id_ = table_id(data_section);
				const auto section_syntax_indicator_ = section_syntax_indicator(data_section);
				if (table_id_ == 0xff)
					break; // stuffing

				// create a key for this section

				bool section_cached = false;

				auto heap_key = std::make_tuple(
					table_id_,
					section_syntax_indicator_ ? table_id_extension(data_section) : 0,
					section_syntax_indicator_ ? section_number(data_section) : 0);

				if (section_syntax_indicator_ && !current_next_indicator(data_section)) // future data
					goto nocaching;

				{
					std::shared_lock<std::shared_mutex> lock(mutex);
					if (heap.find(heap_key) != heap.end())
					{
						// section already cached
						if (section_syntax_indicator_ ? version_number(data_section) : 0 == // equal version?
							section_syntax_indicator(heap[heap_key].psi_data()) ? version_number(heap[heap_key].psi_data()) : 0)
							goto nocaching;
					} // else: section not cached
				}

				// caching:
				// we need this section
				open_sections[pid] = PSISection<_Alloc>();

				open_sections[pid].section_length = section_length(data_section) + 3;
				open_sections[pid].section_data.reserve(open_sections[pid].sizechars());
				open_sections[pid].heap_key = heap_key;

				if ((data.cend() - payload) < static_cast<signed>(open_sections[pid].sizechars())) {
					std::copy(payload, data.cend(), std::back_inserter(open_sections[pid].section_data));
					break; // we won't complete the section in this packet
				}
				else {
					std::copy(payload, payload + open_sections[pid].sizechars(), std::back_inserter(open_sections[pid].section_data));
					payload += open_sections[pid].sizechars();

					// finished
					{
						std::unique_lock<std::shared_mutex> lock(mutex);
						heap[heap_key] = std::move(open_sections[pid]);
					}
					open_sections.erase(pid);

					if (auto x = transfer_callback.lock())
						x->operator()(heap[heap_key].section_data);

					continue;
				}


			nocaching:
				{

					// no caching necessary
					auto section_length_ = section_length(data_section) + 3;
					if ((data.cend() - payload) > static_cast<signed>(section_length_)) {
						payload += section_length_;
						continue;
					}
					else
						break;
				}


			}
		}

	}


	std::map<section_identifier, PSISection<_Alloc>>	heap; // storage
	std::map<uint_fast16_t, PSISection<_Alloc>>			open_sections; // PID -> data
	mutable std::shared_mutex							mutex;

	std::weak_ptr<ProcessNode>							transfer_callback;

};

}

