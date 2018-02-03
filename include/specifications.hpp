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

#include "span_reader.hpp"

namespace tssi
{
	
	/****t* tssi/R1
	*  NAME
	*    R1 -- Reads a byte
	*             - at offset or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               offset
	*    and returns the bit at bit_position.
	*  SOURCE
	*/
	template <size_t offset, size_t bit_position, size_t loop_length = 0>
	using R1 = bit_reader<basic_reader<offset, loop_length>, bit_position>;
	/*******/

	/****t* tssi/R8
	*  NAME
	*    R8 -- Reads 8 bits
	*             - at offset or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               offset.
	*  SOURCE
	*/
	template <size_t offset, size_t loop_length = 0>
	using R8 = endian_aware_value_reader<uint_fast8_t, basic_reader<offset, loop_length>, 1>;
	/*******/

	/****t* tssi/R16
	*  NAME
	*    R16 -- Reads 8 bits
	*             - at offset or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               offset.
	*  SOURCE
	*/
	template <size_t offset, size_t loop_length = 0>
	using R16 = endian_aware_value_reader<uint_fast16_t, basic_reader<offset, loop_length>, 2>;
	/*******/

	/****t* tssi/R24
	*  NAME
	*    R24 -- Reads 24 bits
	*             - at offset or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               offset.
	*  SOURCE
	*/
	template <size_t offset, size_t loop_length = 0>
	using R24 = endian_aware_value_reader<uint_fast32_t, basic_reader<offset, loop_length>, 3>;
	/*******/

	/****t* tssi/R32
	*  NAME
	*    R32 -- Reads 32 bits
	*             - at offset or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               offset.
	*  SOURCE
	*/
	template <size_t offset, size_t loop_length = 0>
	using R32 = endian_aware_value_reader<uint_fast32_t, basic_reader<offset, loop_length>, 4>;
	/*******/

	/****t* tssi/R40
	*  NAME
	*    R40 -- Reads 40 bits
	*             - at offset or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               offset.
	*  SOURCE
	*/
	template <size_t offset, size_t loop_length = 0>
	using R40 = endian_aware_value_reader<uint_fast64_t, basic_reader<offset, loop_length>, 5>;
	/*******/

	/****t* tssi/R64
	*  NAME
	*    R64 -- Reads 64 bits
	*             - at offset or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               offset.
	*  SOURCE
	*/
	template <size_t offset, size_t loop_length = 0>
	using R64 = endian_aware_value_reader<uint_fast64_t, basic_reader<offset, loop_length>, 8>;
	/*******/

	/****t* tssi/ADD_R1
	*  NAME
	*    ADD_R1 -- Reads a byte
	*             - at (reference + offset) or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               (reference + offset)
	*    and returns the bit at bit_position.
	*  SOURCE
	*/		
	template <class reference, size_t offset, size_t bit_position, size_t loop_length = 0>
	using ADD_R1 = bit_reader<combined_reader<
		basic_reader<offset, loop_length>, reference>, bit_position>;
	/*******/

	/****t* tssi/ADD_R8
	*  NAME
	*    ADD_R8 -- Reads 8 bits
	*             - at (reference + offset) or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               (reference + offset).
	*  SOURCE
	*/
	template <class reference, size_t offset, size_t loop_length = 0>
	using ADD_R8 = endian_aware_value_reader<
		uint_fast8_t, combined_reader<basic_reader<offset, loop_length>, reference>, 1>;
	/*******/

	/****t* tssi/ADD_R16
	*  NAME
	*    ADD_R16 -- Reads 16 bits
	*             - at (reference + offset) or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               (reference + offset).
	*  SOURCE
	*/
	template <class reference, size_t offset, size_t loop_length = 0>
	using ADD_R16 = endian_aware_value_reader<
		uint_fast16_t, combined_reader<basic_reader<offset, loop_length>, reference>, 2>;
	/*******/

	/****t* tssi/ADD_R24
	*  NAME
	*    ADD_R24 -- Reads 24 bits
	*             - at (reference + offset) or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               (reference + offset).
	*  SOURCE
	*/
	template <class reference, size_t offset, size_t loop_length = 0>
	using ADD_R24 = endian_aware_value_reader<
		uint_fast32_t, combined_reader<basic_reader<offset, loop_length>, reference>, 3>;
	/*******/

	/****t* tssi/ADD_R32
	*  NAME
	*    ADD_R32 -- Reads 32 bits
	*             - at (reference + offset) or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               (reference + offset).
	*  SOURCE
	*/
	template <class reference, size_t offset, size_t loop_length = 0>
	using ADD_R32 = endian_aware_value_reader<
		uint_fast32_t, combined_reader<basic_reader<offset, loop_length>, reference>, 4>;
	/*******/

	/****t* tssi/ADD_R40
	*  NAME
	*    ADD_R40 -- Reads 40 bits
	*             - at (reference + offset) or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               (reference + offset).
	*  SOURCE
	*/
	template <class reference, size_t offset, size_t loop_length = 0>
	using ADD_R40 = endian_aware_value_reader<
		uint_fast64_t, combined_reader<basic_reader<offset, loop_length>, reference>, 5>;
	/*******/

	/****t* tssi/ADD_R64
	*  NAME
	*    ADD_R64 -- Reads 64 bits
	*             - at (reference + offset) or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               (reference + offset).
	*  SOURCE
	*/
	template <class reference, size_t offset, size_t loop_length = 0>
	using ADD_R64 = endian_aware_value_reader<
		uint_fast64_t, combined_reader<basic_reader<offset, loop_length>, reference>, 8>;
	/*******/

	/****t* tssi/DAT
	*  NAME
	*    DAT -- Reads a gsl::span<const char> memory buffer
	*             - at offset with length (count_reference + reference_offset) or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               offset with length (count_reference + reference_offset).
	*  SOURCE
	*/
	template <size_t offset, class count_reference, ptrdiff_t reference_offset = 0, size_t loop_length = 0>
	using DAT = span_reader<offset, count_reference, reference_offset, loop_length>;
	/*******/

	/****t* tssi/ADD_DAT
	*  NAME
	*    ADD_DAT -- Reads a gsl::span<const char> memory buffer
	*             - at (reference + offset) with length (count_reference +
	*               reference_offset) or
	*             - in an i-th iteration of a loop with fixed loop size loop_length at
	*               (reference + offset) with length (count_reference + reference_offset).
	*  SOURCE
	*/
	template <class reference, size_t offset, class count_reference, ptrdiff_t reference_offset = 0, size_t loop_length = 0>
	using ADD_DAT = combined_reader<span_reader
		<offset, count_reference, reference_offset, loop_length>, reference>;
	/*******/

	/****t* tssi/ADD
	*  NAME
	*    ADD -- Calculates the sum of two references.
	*  SOURCE
	*/
	template <class reference_a, class reference_b>
	using ADD = reference_sum<reference_a, reference_b>;
	/*******/

	/****t* tssi/SUB
	*  NAME
	*    SUB -- Calculates the difference of two references.
	*  SOURCE
	*/
	template <class reference_a, class reference_b>
	using SUB = reference_difference<reference_a, reference_b>;
	/*******/

	/****t* tssi/MS
	*  NAME
	*    MS -- Performs a bitwise and followed by a shift right operation on the given value:
	*          (value & mask) >> shift
	*  SOURCE
	*/
	template <class value, uint_fast64_t mask, uint_fast64_t shift>
	using MS = mask_shift<value, mask, shift>;
	/*******/

	/****t* tssi/TIME
	*  NAME
	*    TIME -- Converts an ETSI 300 468 Annex C-typed time value to time_c.
	*  SOURCE
	*/
	template <class value> 
	using TIME = time_convert<value>;
	/*******/

	/****t* tssi/DUR
	*  NAME
	*    DUR -- Converts a six digit (hh::mm:ss) BCD duration value to 
	*    std::chrono::seconds.
	*  SOURCE
	*/
	template <class duration>
	using DUR = duration_convert<duration>;
	/*******/

	/****t* tssi/CHAR
	*  NAME
	*    CHAR -- Converts an ETSI EN 300468 Annex A (Text) memory buffer to utf-8
	*    carried within std::string. The returned object is a std::pair of bool and
	*    std::string. The bool is true if the conversion was successful otherwise it
	*    the string contains an error message.
	*  NOTES
	*    CHAR may throw exceptions (see std::string).
	*  SOURCE
	*/
	template <class span>
	using CHAR = string_reader<span>;
	/*******/

	/****t* tssi/BCD
	*  NAME
	*    BCD -- Decodes a given BCD value. 
	*  SOURCE
	*/
	template <class value, size_t digits>
	using BCD = bcd_convert<value, digits>;
	/*******/

	/****t* tssi/ITER
	*  NAME
	*    ITER -- Associates data (gsl::span<const char>) with syntax (structure). Therefore,
	*    allows to iterate through data loops of variables sizes by utilizing
	*    range_span, range_span_iterator and range for.
	*    e.g.
	*       for (auto loop : range_span_ITER(data)) {}
	*  SOURCE
	*/
	template <class span, tssi_size_t structure>
	using ITER = iterable_span<span, structure>;
	/*******/



#define TSSI_MTD_ESC(...) __VA_ARGS__

#define TSSI_MTD_FAC(classname, functionname) \
	inline auto functionname(gsl::span<const char> data, size_t index = 0) \
	noexcept(noexcept(classname::at(data, index))) \
	{ return classname::at(data, index); }

/****d* tssi/TSSI_MTD
*  NAME
*    TSSI_MTD -- Function factory. Defines functions with the signature
*        inline [return_type] functionname (gsl::span<const char> data, size_t index = 0);
*  NOTES
*    The functions does not throw if the underlying reader does not throw.
*  SOURCE
*/
#define TSSI_MTD(classname, functionname) TSSI_MTD_FAC(TSSI_MTD_ESC classname, functionname)
/*******/

	namespace iso138183 {

		/****h* tssi::iso138183/frame_header
		*  NAME
		*    frame_header -- MPEG Audio frame header, version 1 (ISO 11172-3), 
		*    version 2 (ISO 13818-3), and version 2.5
		*  SOURCE
		*/
		namespace frame_header {
			TSSI_MTD((MS<R16<0>, 0xffe0, 5>),
				frame_sync);
			TSSI_MTD((MS<R8<1>, 0x18, 3>),
				mpeg_audio_version);
			TSSI_MTD((MS<R8<1>, 0x6, 1>),
				layer_description);
			TSSI_MTD((R1<1, 7>),
				crc_protection_bit);
			TSSI_MTD((MS<R8<2>, 0xf0, 4>),
				bitrate_index);
			TSSI_MTD((MS<R8<2>, 0xc, 2>),
				sampling_rate_index);
			TSSI_MTD((R1<2, 6>),
				padding_bit);
			TSSI_MTD((R1<2, 7>),
				private_bit);
			TSSI_MTD((MS<R8<3>, 0xc0, 6>),
				channel_mode);
			TSSI_MTD((MS<R8<3>, 0x30, 4>),
				mode_extension);
			TSSI_MTD((R1<3, 4>),
				copyright_bit);
			TSSI_MTD((R1<3, 5>),
				original_media_bit);
			TSSI_MTD((MS<R8<3>, 0x03, 0>),
				emphasis);
		}
		/*******/

	}

	namespace iso138181 {

		/****h* tssi::iso138181/transport_packet
		*  NAME
		*    transport_packet -- Basic unit of an MPEG transport stream, 188 byte in length
		*  SOURCE
		*/
		namespace transport_packet {
			TSSI_MTD((R8<0>),
				sync_byte);
			TSSI_MTD((R1<1, 7>),
				transport_error_indicator);
			TSSI_MTD((R1<1, 6>),
				payload_unit_start_indicator);
			TSSI_MTD((R1<1, 5>),
				transport_priority);
			TSSI_MTD((MS<R16<1>, 0x1fff, 0>),
				PID);
			TSSI_MTD((MS<R8<3>, 0xc0, 6>),
				transport_scrambling_control);
			TSSI_MTD((MS<R8<3>, 0x30, 4>),
				adaptation_field_control);
			TSSI_MTD((MS<R8<3>, 0x0f, 0>),
				continuity_counter);
		}
		/*******/

		/****h* tssi::iso138181/adaptation_field
		*  NAME
		*    adaptation_field -- Optional field included after transport_packet if
		*    adaptation_field_control is equal to 0x2 or 0x3.
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace adaptation_field {
			TSSI_MTD((R8<0>),
				adaptation_field_length);
			// if (adaptation_field_length > 0) { 
			TSSI_MTD((R1<1, 7>),
				discontinuity_indicator);
			TSSI_MTD((R1<1, 6>),
				random_access_indicator);
			TSSI_MTD((R1<1, 5>),
				elementary_stream_priority_indicator);
			TSSI_MTD((R1<1, 4>),
				PCR_flag);
			TSSI_MTD((R1<1, 3>),
				OPCR_flag);
			TSSI_MTD((R1<1, 2>),
				splicing_point_flag);
			TSSI_MTD((R1<1, 1>),
				transport_private_data_flag);
			TSSI_MTD((R1<1, 0>),
				adaptation_field_extension_flag);
			// if (PCR_flag == 1) {
			TSSI_MTD((MS<R64<2>, 0xffffffff80000000, 31>),
				program_clock_reference_base);
			TSSI_MTD((MS<R16<6>, 0x1ff, 0>),
				program_clock_reference_extension);
			// }
			// }
		}
		/*******/

		/****h* tssi::iso138181/PES_packet
		*  NAME
		*    PES_packet -- Packetized Elementary Stream (PES) packets are used to carry
		*    elementary streams.
		*  NOTES
		*    Make use of appropriate derived classes if stream_id is known.
		*  DERIVED BY
		*    PES_packet_media, PES_packet_auxiliary
		*  SOURCE
		*/
		namespace PES_packet {
			TSSI_MTD((R24<0>),
				packet_start_code_prefix);
			TSSI_MTD((R8<3>),
				stream_id);
			TSSI_MTD((R16<4>),
				PES_packet_length);
		}
		/*******/

		/****h* tssi::iso138181/PES_packet_media
		*  NAME
		*    PES_packet_media -- Packetized Elementary Stream (PES) packets carrying a
		*    sophisticated header
		*  SOURCE
		*/
		namespace PES_packet_media {
			using namespace PES_packet;
			// if (stream_id != program_stream_map
			//	&& stream_id != padding_stream
			//	&& stream_id != private_stream_2
			//	&& stream_id != ECM
			//	&& stream_id != EMM
			//	&& stream_id != program_stream_directory
			//	&& stream_id != DSMCC_stream
			//	&& stream_id != ITU - T Rec.H.222.1 type E stream) {
			TSSI_MTD((MS<R8<6>, 0xc0, 6>),
				_signature1); // == 0x2
			TSSI_MTD((MS<R8<6>, 0x30, 4>),
				PES_scrambling_control);
			TSSI_MTD((R1<6, 3>),
				PES_priority);
			TSSI_MTD((R1<6, 2>),
				data_alignment_indicator);
			TSSI_MTD((R1<6, 1>),
				copyright);
			TSSI_MTD((R1<6, 0>),
				original_or_copy);
			TSSI_MTD((MS<R8<7>, 0xc0, 6>),
				PTS_DTS_flags);
			TSSI_MTD((R1<7, 5>),
				ESCR_flag);
			TSSI_MTD((R1<7, 4>),
				ES_rate_flag);
			TSSI_MTD((R1<7, 3>),
				DSM_trick_mode_flag);
			TSSI_MTD((R1<7, 2>),
				additional_copy_info_flag);
			TSSI_MTD((R1<7, 1>),
				PES_CRC_flag);
			TSSI_MTD((R1<7, 0>),
				PES_extension_flag);
			TSSI_MTD((R8<8>),
				PES_header_data_length);

			// if ((PTS_DTS_flags & 0x2) == 0x2) { 
			TSSI_MTD((MS<R8<9>, 0xf0, 4>),
				_signature2); // == PTS_DTS_flags
			TSSI_MTD((MS<R8<9>, 0xe0, 1>),
				PTS_32_30);
			TSSI_MTD((R1<9, 0>),
				marker_bit1); // == 1
			TSSI_MTD((MS<R16<10>, 0xfffe, 1>),
				PTS_29_15);
			TSSI_MTD((R1<11, 0>),
				marker_bit2); // == 1
			TSSI_MTD((MS<R16<12>, 0xfffe, 1>),
				PTS_14_0);
			TSSI_MTD((R1<13, 0>),
				marker_bit3); // == 1
			inline uint_fast64_t PTS(gsl::span<const char> data) noexcept {
				return static_cast<uint_fast64_t>(PTS_14_0(data)) | (static_cast<uint_fast64_t>(PTS_29_15(data)) << 15) | (static_cast<uint_fast64_t>(PTS_32_30(data)) << 30);
			}

			// if ((PTS_DTS_flags & 0x1) == 0x1) { 
			TSSI_MTD((MS<R8<14>, 0xf0, 4>),
				_signature3); // == 0x1
			TSSI_MTD((MS<R8<14>, 0xe0, 1>),
				DTS_32_30);
			TSSI_MTD((R1<14, 0>),
				marker_bit4); // == 1
			TSSI_MTD((MS<R16<15>, 0xfffe, 1>),
				DTS_29_15);
			TSSI_MTD((R1<16, 0>),
				marker_bit5); // == 1
			TSSI_MTD((MS<R16<17>, 0xfffe, 1>),
				DTS_14_0);
			TSSI_MTD((R1<18, 0>),
				marker_bit6); // == 1
			inline uint_fast64_t DTS(gsl::span<const char> data) noexcept {
				return static_cast<uint_fast64_t>(DTS_14_0(data)) | (static_cast<uint_fast64_t>(DTS_29_15(data)) << 15) | (static_cast<uint_fast64_t>(DTS_32_30(data)) << 30);
			}

			// } DTS

			// } PTS


			inline gsl::span<const char> PES_packet_data_bytes(gsl::span<const char> data) noexcept
			{
				auto header_length = PES_header_data_length(data) + 9;
				if (header_length <= data.size())
					return data.subspan(PES_header_data_length(data) + 9);
				else
					return data.subspan(data.size());
			}

			// }
		}
		/*******/

		/****h* tssi::iso138181/PES_packet_auxiliary
		*  NAME
		*    PES_packet_auxiliary -- Packetized Elementary Stream (PES) packets with thin header
		*  SOURCE
		*/
		namespace PES_packet_auxiliary {
			using namespace PES_packet;
			namespace {
				using PES_packet_length_t =
					R16<4>;
			}

			// if (stream_id == program_stream_map
			//	|| stream_id == private_stream_2
			//	|| stream_id == ECM
			//	|| stream_id == EMM
			//	|| stream_id == program_stream_directory
			//	|| stream_id == DSMCC_stream
			//	|| stream_id == ITU - T Rec.H.222.1 type E stream) {
			TSSI_MTD((DAT<6, PES_packet_length_t>),
				PES_packet_data_bytes);
			// }
		}
		/*******/

		/****h* tssi::iso138181/descriptor
		*  NAME
		*    descriptor -- "[D]escriptors are namespaceures which may be used to extend the
		*    definitions of [other elements]" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace descriptor {
			TSSI_MTD((R8<0>),
				descriptor_tag);
			TSSI_MTD((R8<1>),
				descriptor_length);

			inline ptrdiff_t size(gsl::span<const char> data) noexcept { return descriptor_length(data) + 2; }
		}
		/*******/

	}


	/****h* tssi/descriptor_loop
	*  NAME
	*    descriptor_loop -- Helper to define the length of single desriptors in
	*    descriptor lists for range_span.
	*  SOURCE
	*/
	namespace descriptor_loop = iso138181::descriptor;
	/*******/

	namespace iso138181 {


		/****h* tssi::iso138181/private_section
		*  NAME
		*    private_section -- The syntax of a private section is the basic template for all
		*    PSI sections.
		*  DERIVED BY
		*    private_section_syntax
		*  SOURCE
		*/
		namespace private_section {
			TSSI_MTD((R8<0>),
				table_id);
			TSSI_MTD((R1<1, 7>),
				section_syntax_indicator);
			TSSI_MTD((R1<1, 6>),
				private_indicator);
			TSSI_MTD((MS<R16<1>, 0xfff, 0>),
				section_length);
			// private_data_bytes
		}
		/*******/

		/****h* tssi::iso138181/private_section_syntax
		*  NAME
		*    private_section_syntax -- PSI section with section_syntax_indicator == 1. Allows
		*    for versioning, multiple sections and crc32-checks.
		*  SOURCE
		*/
		namespace private_section_syntax {
			using namespace private_section;

			TSSI_MTD((R16<3>),
				table_id_extension);
			TSSI_MTD((MS<R8<5>, 0x3e, 1>),
				version_number);
			TSSI_MTD((R1<5, 0>),
				current_next_indicator);
			TSSI_MTD((R8<6>),
				section_number);
			TSSI_MTD((R8<7>),
				last_section_number);
			// private_data_bytes
			// CRC_32
		}
		/*******/

		/****h* tssi::iso138181/program_association_section
		*  NAME
		*    program_association_section -- "The Program Association Table provides
		*    the correspondence between a program_number and the PID value of the
		*    Transport Stream packets which carry the program definition. The program_number
		*    is the numeric label associated with a program" [ISO/IEC 13818-1, 2nd edition].
		*    - PID: 0x00
		*    - table_id: 0x00
		*  SOURCE
		*/
		namespace program_association_section {
			using namespace private_section_syntax;

			TSSI_MTD((R16<3>),
				transport_stream_id);

			inline size_t N(gsl::span<const char> data) noexcept { return (section_length(data) - 9) >> 2; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R16<8, 4>),
				program_number);
			TSSI_MTD((MS<R16<8 + 2, 4>, 0x1fff, 0>),
				program_map_PID);
			// }
			// CRC_32
		}
		/*******/

		/****h* tssi::iso138181/CA_section
		*  NAME
		*    CA_section -- "The Conditional Access (CA) Table provides the association
		*    between one or more CA systems, their EMM streams and any special parameters
		*    associated with them" [ISO/IEC 13818-1, 2nd edition].
		*    - PID: 0x01
		*    - table_id: 0x01
		*  SOURCE
		*/
		namespace CA_section {
			using namespace private_section_syntax;
			namespace {
				using section_length_t = MS<R16<1>, 0xfff, 0>;
			}
			TSSI_MTD((ITER<DAT<8, section_length_t, -9>, descriptor_loop::size>),
				descriptors);
			// CRC_32
		}
		/*******/

		/****h* tssi::iso138181/TS_program_map_section
		*  NAME
		*    TS_program_map_section -- "The Program Map Table provides the mappings between
		*    program numbers and the program elements that comprise them"
		*    [ISO/IEC 13818-1, 2nd edition].
		*    - PID: indicated in program_association_section
		*    - table_id: 0x02
		*  SOURCE
		*/
		namespace TS_program_map_section {
			using namespace private_section_syntax;
			namespace {
				using program_info_length_t =
					MS<R16<10>, 0xfff, 0>;
				using section_length_t =
					MS<R16<1>, 0xfff, 0>;
			}
			TSSI_MTD((R16<3>),
				program_number);
			TSSI_MTD((MS<R16<8>, 0x1fff, 0>),
				PCR_PID);

			TSSI_MTD((program_info_length_t),
				program_info_length);
			TSSI_MTD((ITER<DAT<12, program_info_length_t>, descriptor_loop::size>),
				descriptors);

			// for (auto loop : program_info_loop(data)) {
			namespace loop {
				namespace {
					using ES_info_length_t =
						MS<R16<3>, 0xfff, 0>;
				}
				TSSI_MTD((R8<0>),
					stream_type);
				TSSI_MTD((MS<R16<1>, 0x1fff, 0>),
					elementary_PID);

				TSSI_MTD((ES_info_length_t),
					ES_info_length);
				TSSI_MTD((ITER<DAT<5, ES_info_length_t>, descriptor_loop::size>),
					descriptors);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return ES_info_length(data) + 5; }
			}
			// }

			TSSI_MTD((ITER<ADD_DAT<program_info_length_t, 12, SUB<section_length_t, program_info_length_t>, -13>, loop::size>),
				program_info_loop);

			// CRC_32
		}
		/*******/

		/****h* tssi::iso138181/TS_description_section
		*  NAME
		*    TS_description_section -- "The Transport Stream Description Table is defined to
		*    support the carriage of descriptors [...] for an entire Transport Stream. The
		*    descriptors shall apply to the entire Transport Stream"
		*    [ISO/IEC 13818-1, 2nd edition].
		*    - PID: 0x02
		*    - table_id: 0x03
		*  SOURCE
		*/
		namespace TS_description_section {
			using namespace private_section_syntax;
			namespace {
				using section_length_t = MS<R16<1>, 0xfff, 0>;
			}

			TSSI_MTD((ITER<DAT<8, section_length_t, -9>, descriptor_loop::size>),
				descriptors);
			// CRC_32
		}
		/*******/

	}

	namespace etsi300468 {

		/****h* tssi::etsi300468/network_information_section
		*  NAME
		*    network_information_section -- "The NIT conveys information relating to the
		*    physical organization of the multiplexes/TSs carried via a given network, and
		*    the characteristics of the network itself" [ETSI EN 300 468 V1.13.1].
		*    - PID: 0x10
		*    - table_id: 0x40 (actual network), 0x41 (other network)
		*  SOURCE
		*/
		namespace network_information_section {
			using namespace iso138181::private_section_syntax;
			namespace {
				using network_descriptors_length_t =
					MS<R16<8>, 0xfff, 0>;
				using transport_stream_loop_length_t =
					MS<ADD_R16<network_descriptors_length_t, 10>, 0xfff, 0>;
			}

			TSSI_MTD((R16<3>),
				network_id);

			TSSI_MTD((network_descriptors_length_t),
				network_descriptors_length);
			TSSI_MTD((ITER<DAT<10, network_descriptors_length_t>, descriptor_loop::size>),
				descriptors);

			TSSI_MTD((transport_stream_loop_length_t),
				transport_stream_loop_length);

			// for (auto loop : transport_stream_loop(data)) {
			namespace loop {
				namespace {
					using transport_descriptors_length_t =
						MS<R16<4>, 0xfff, 0>;
				}

				TSSI_MTD((R16<0>),
					transport_stream_id);
				TSSI_MTD((R16<2>),
					original_network_id);
				TSSI_MTD((transport_descriptors_length_t),
					transport_descriptors_length);
				TSSI_MTD((ITER<DAT<6, transport_descriptors_length_t>, descriptor_loop::size>),
					descriptors);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return transport_descriptors_length(data) + 6; }
			}
			// }

			TSSI_MTD((ITER<ADD_DAT<network_descriptors_length_t, 12, transport_stream_loop_length_t>, loop::size>),
				transport_stream_loop);


			// CRC_32
		}
		/*******/

		/****h* tssi::etsi300468/bouquet_association_section
		*  NAME
		*    bouquet_association_section -- "The BAT provides information regarding
		*    bouquets. A bouquet is a collection of services, which may traverse the boundary
		*    of a network" [ETSI EN 300 468 V1.13.1].
		*    - PID: 0x11
		*    - table_id: 0x4a
		*  SOURCE
		*/
		namespace bouquet_association_section {
			using namespace iso138181::private_section_syntax;
			namespace {
				using bouquet_descriptors_length_t =
					MS<R16<8>, 0xfff, 0>;
				using transport_stream_loop_length_t =
					MS<ADD_R16<bouquet_descriptors_length_t, 10>, 0xfff, 0>;
			}

			TSSI_MTD((R16<3>),
				bouquet_id);
			TSSI_MTD((bouquet_descriptors_length_t),
				bouquet_descriptors_length);
			TSSI_MTD((ITER<DAT<10, bouquet_descriptors_length_t>, descriptor_loop::size>),
				descriptors);
			TSSI_MTD((transport_stream_loop_length_t),
				transport_stream_loop_length);

			// for (auto loop : transport_stream_loop(data)) {
			namespace loop {
				namespace {
					using transport_descriptors_length_t =
						MS<R16<4>, 0xfff, 0>;
				}
				TSSI_MTD((R16<0>),
					transport_stream_id);
				TSSI_MTD((R16<2>),
					original_network_id);
				TSSI_MTD((transport_descriptors_length_t),
					transport_descriptors_length);
				TSSI_MTD((ITER<DAT<6, transport_descriptors_length_t>, descriptor_loop::size>),
					descriptors);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return transport_descriptors_length(data) + 6; }
			}
			// }

			TSSI_MTD((ITER<ADD_DAT<bouquet_descriptors_length_t, 12, transport_stream_loop_length_t>, loop::size>),
				transport_stream_loop);

			// CRC_32
		}
		/*******/

		/****h* tssi::etsi300468/service_description_section
		*  NAME
		*    service_description_section -- "Each sub_table of the SDT shall describe services
		*    that are contained within a particular TS. The services may be part of the actual
		*    TS or part of other TSs" [ETSI EN 300 468 V1.13.1].
		*    - PID: 0x11
		*    - table_id: 0x42 (actual TS), 0x46 (other TS)
		*  SOURCE
		*/
		namespace service_description_section {
			using namespace iso138181::private_section_syntax;
			namespace {
				using section_length_t =
					MS<R16<1>, 0xfff, 0>;
			}

			TSSI_MTD((R16<3>),
				transport_stream_id);
			TSSI_MTD((R16<8>),
				original_network_id);

			// for (auto loop : service_info_loop(data)) {
			namespace loop {
				namespace {
					using descriptors_loop_length_t =
						MS<R16<3>, 0xfff, 0>;
				}
				TSSI_MTD((R16<0>),
					service_id);
				TSSI_MTD((R1<2, 1>),
					EIT_schedule_flag);
				TSSI_MTD((R1<2, 0>),
					EIT_present_following_flag);
				TSSI_MTD((MS<R8<3>, 0xe0, 5>),
					running_status);
				TSSI_MTD((R1<3, 4>),
					free_CA_mode);
				TSSI_MTD((descriptors_loop_length_t),
					descriptors_loop_length);
				TSSI_MTD((ITER<DAT<5, descriptors_loop_length_t>, descriptor_loop::size>),
					descriptors);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return descriptors_loop_length(data) + 5; }

			}
			// }

			TSSI_MTD((ITER<DAT<11, section_length_t, -12>, loop::size>),
				service_info_loop);

			// CRC_32
		}
		/*******/

		/****h* tssi::etsi300468/event_information_section
		*  NAME
		*    event_information_section -- "The EIT provides information in chronological order
		*    regarding the events contained within each service" [ETSI EN 300 468 V1.13.1].
		*    - PID: 0x12
		*    - table_id: 0x4e (actual ts, present and following events)
		*                0x4f (other ts, present and following events)
		*                0x50 to 0x5f (actual ts, schedule)
		*                0x60 to 0x6f (other ts, schedule)
		*  SOURCE
		*/
		namespace event_information_section {
			using namespace iso138181::private_section_syntax;
			namespace {
				using section_length_t =
					MS<R16<1>, 0xfff, 0>;
			}

			TSSI_MTD((R16<3>),
				service_id);
			TSSI_MTD((R16<8>),
				transport_stream_id);
			TSSI_MTD((R16<10>),
				original_network_id);
			TSSI_MTD((R8<12>),
				segment_last_section_number);
			TSSI_MTD((R8<13>),
				last_table_id);

			// for (auto loop : event_info_loop(data)) {
			namespace loop {
				namespace {
					using descriptors_loop_length_t =
						MS<R16<10>, 0xfff, 0>;
				}
				TSSI_MTD((R16<0>),
					event_id);
				TSSI_MTD((TIME<R40<2>>),
					start_time);
				TSSI_MTD((DUR<R24<7>>),
					duration);
				TSSI_MTD((MS<R8<10>, 0xe0, 5>),
					running_status);
				TSSI_MTD((R1<10, 4>),
					free_CA_mode);
				TSSI_MTD((descriptors_loop_length_t),
					descriptors_loop_length);
				TSSI_MTD((ITER<DAT<12, descriptors_loop_length_t>, descriptor_loop::size>),
					descriptors);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return descriptors_loop_length(data) + 12; }

			}
			// }

			TSSI_MTD((ITER<DAT<14, section_length_t, -15>, loop::size>),
				event_info_loop);

			// CRC_32
		}
		/*******/

		/****h* tssi::etsi300468/time_date_section
		*  NAME
		*    time_date_section -- "The TDT carries only the UTC-time and date information"
		*    [ETSI EN 300 468 V1.13.1].
		*    - PID: 0x14
		*    - table_id: 0x70
		*  SOURCE
		*/
		namespace time_date_section {
			using namespace iso138181::private_section;

			TSSI_MTD((TIME<R40<3>>),
				UTC_time);
		}
		/*******/

		/****h* tssi::etsi300468/time_offset_section
		*  NAME
		*    time_offset_section -- "The TOT (see table 9) carries the UTC-time and date
		*    information and local time offset" [ETSI EN 300 468 V1.13.1].
		*    - PID: 0x14
		*    - table_id: 0x73
		*  SOURCE
		*/
		namespace time_offset_section {
			using namespace iso138181::private_section;
			namespace {
				using descriptors_loop_length_t =
					MS<R16<8>, 0xfff, 0>;
			}

			TSSI_MTD((TIME<R40<3>>),
				UTC_time);
			TSSI_MTD((descriptors_loop_length_t),
				descriptors_loop_length);
			TSSI_MTD((ITER<DAT<10, descriptors_loop_length_t>, descriptor_loop::size>),
				descriptors);
		}
		/*******/

		/****h* tssi::etsi300468/running_status_section
		*  NAME
		*    running_status_section -- "The RST (see table 10) allows accurate and rapid
		*    updating of the timing status of one or more events" [ETSI EN 300 468 V1.13.1].
		*    - PID: 0x13
		*    - table_id: 0x71
		*  SOURCE
		*/
		namespace running_status_section {
			using namespace iso138181::private_section;

			inline size_t N(gsl::span<const char> data) noexcept { return section_length(data) / 9; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R16<3, 9>),
				transport_stream_id);
			TSSI_MTD((R16<3 + 2, 9>),
				original_network_id);
			TSSI_MTD((R16<3 + 4, 9>),
				service_id);
			TSSI_MTD((R16<3 + 6, 9>),
				event_id);
			TSSI_MTD((MS<R8<3 + 8, 9>, 0x7, 0>),
				running_status);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/stuffing_section
		*  NAME
		*    stuffing_section -- "The purpose of this [section] is to invalidate existing
		*    sections at a delivery system boundary e.g. at a cable head-end."
		*    [ETSI EN 300 468 V1.13.1].
		*    - PID: 0x10, 0x11, 0x12, 0x13, 0x14
		*    - table_id: 0x72
		*  SOURCE
		*/
		namespace stuffing_section {
			using namespace iso138181::private_section;
			// stuffing_bytes
		}
		/*******/

		/****h* tssi::etsi300468/discontinuity_information_section
		*  NAME
		*    discontinuity_information_section -- "The DIT is to be inserted at transition
		*    points at which SI information may be discontinuous."
		*    [ETSI EN 300 468 V1.13.1].
		*    - PID: 0x1e
		*    - table_id: 0x7e
		*  SOURCE
		*/
		namespace discontinuity_information_section {
			using namespace iso138181::private_section;
			TSSI_MTD((R1<3, 7>),
				transition_flag);
		}
		/*******/

		/****h* tssi::etsi300468/selection_information_section
		*  NAME
		*    selection_information_section -- "The SIT describes the service(s) and event(s)
		*    carried by [a] "partial" TS" [ETSI EN 300 468 V1.13.1].
		*    - PID: 0x1f
		*    - table_id: 0x7f
		*  SOURCE
		*/
		namespace selection_information_section {
			using namespace iso138181::private_section_syntax;
			namespace {
				using transmission_info_loop_length_t =
					MS<R16<8>, 0xfff, 0>;
				using section_length_t =
					MS<R16<1>, 0xfff, 0>;
			}

			TSSI_MTD((transmission_info_loop_length_t),
				transmission_info_loop_length);
			TSSI_MTD((ITER<DAT<10, transmission_info_loop_length_t>, descriptor_loop::size>),
				descriptors);

			// for (auto loop : transmission_info_loop(data)) {
			namespace loop {
				namespace {
					using service_loop_length_t =
						MS<R16<2>, 0xfff, 0>;
				}
				TSSI_MTD((R16<0>),
					service_id);
				TSSI_MTD((MS<R8<2>, 0x70, 4>),
					running_status);
				TSSI_MTD((service_loop_length_t),
					service_loop_length);
				TSSI_MTD((ITER<DAT<4, service_loop_length_t>, descriptor_loop::size>),
					descriptors);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return service_loop_length(data) + 4; }

			}
			// }

			TSSI_MTD((ITER<ADD_DAT<transmission_info_loop_length_t, 10, SUB<section_length_t, transmission_info_loop_length_t>, -11>, loop::size>),
				transmission_info_loop);

			// CRC_32
		}
		/*******/

	}

	namespace iso138181 {

		/****h* tssi::iso138181/video_stream_descriptor
		*  NAME
		*    video_stream_descriptor -- "The video_stream_descriptor provides basic information
		*    which identifies the coding parameters of a video elementary stream"
		*    [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace video_stream_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 0x02;
			TSSI_MTD((R1<2, 7>),
				multiple_frame_rate_flag);
			TSSI_MTD((MS<R8<2>, 0x78, 3>),
				frame_rate_code);
			TSSI_MTD((R1<2, 2>),
				MPEG_1_only_flag);
			TSSI_MTD((R1<2, 1>),
				constrained_parameter_flag);
			TSSI_MTD((R1<2, 0>),
				still_picture_flag);

			// if (MPEG_1_only_flag == '0') {
			TSSI_MTD((R8<3>),
				profile_and_level_indication);
			TSSI_MTD((MS<R8<4>, 0xc0, 6>),
				chroma_format);
			TSSI_MTD((R1<4, 5>),
				frame_rate_extension_flag);
			// }
		}
		/*******/

		/****h* tssi::iso138181/audio_stream_descriptor
		*  NAME
		*    audio_stream_descriptor -- "The audio_stream_descriptor provides basic information
		*    which identifies the coding version of an audio elementary stream"
		*    [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace audio_stream_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 0x03;
			TSSI_MTD((R1<2, 7>),
				free_format_flag);
			TSSI_MTD((R1<2, 6>),
				ID);
			TSSI_MTD((MS<R8<2>, 0x30, 4>),
				layer);
			TSSI_MTD((R1<2, 3>),
				variable_rate_audio_indicator);
		}
		/*******/

		/****h* tssi::iso138181/hierarchy_descriptor
		*  NAME
		*    hierarchy_descriptor -- "The hierarchy_descriptor provides information to identify
		*    the program elements containing components of hierarchically-coded video and
		*    audio, and private streams" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace hierarchy_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 0x04;
			TSSI_MTD((MS<R8<2>, 0xf, 0>),
				hierarchy_type);
			TSSI_MTD((MS<R8<3>, 0x3f, 0>),
				hierarchy_layer_index);
			TSSI_MTD((MS<R8<3>, 0x3f, 0>),
				hierarchy_embedded_layer_index);
			TSSI_MTD((MS<R8<3>, 0x3f, 0>),
				hierarchy_channel);
		}
		/*******/

		/****h* tssi::iso138181/registration_descriptor
		*  NAME
		*    registration_descriptor -- "The registration_descriptor provides a method to
		*    uniquely and unambiguously identify formats of private data"
		*    [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace registration_descriptor {
			using namespace descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x05;
			TSSI_MTD((R32<2>),
				format_identifier);
			TSSI_MTD((DAT<6, descriptor_length_t, -4>),
				additional_identification_info);
		}
		/*******/

		/****h* tssi::iso138181/data_stream_alignment_descriptor
		*  NAME
		*    data_stream_alignment_descriptor -- "The data_stream_alignment_descriptor
		*    describes which type of alignment is present in the associated elementary
		*    stream." [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace data_stream_alignment_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 0x06;
			TSSI_MTD((R8<2>),
				alignment_type);
		}
		/*******/

		/****h* tssi::iso138181/target_background_grid_descriptor
		*  NAME
		*    target_background_grid_descriptor -- "It is possible to have one or more video
		*    streams which, when decoded, are not intended to occupy the full display area
		*    (e.g. a monitor). The combination of target_background_grid_descriptor and
		*    video_window_descriptor[s] allows the display of these video windows in their
		*    desired locations." [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace target_background_grid_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 0x07;
			TSSI_MTD((MS<R16<2>, 0xfffc, 2>),
				horizontal_size);
			TSSI_MTD((MS<R32<2>, 0x3fff0, 4>),
				vertical_size);
			TSSI_MTD((MS<R8<5>, 0xf, 0>),
				aspect_ratio_information);
		}
		/*******/

		/****h* tssi::iso138181/video_window_descriptor
		*  NAME
		*    video_window_descriptor -- "The video_window_descriptor is used to describe the
		*    window characteristics of the associated video elementary stream. Its values
		*    reference the target_background_grid_descriptor for the same stream"
		*    [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace video_window_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 0x08;
			TSSI_MTD((MS<R16<2>, 0xfffc, 2>),
				horizontal_offset);
			TSSI_MTD((MS<R32<2>, 0x3fff0, 4>),
				vertical_offset);
			TSSI_MTD((MS<R8<5>, 0xf, 0>),
				window_priority);
		}
		/*******/

		/****h* tssi::iso138181/CA_descriptor
		*  NAME
		*    CA_descriptor -- "The CA_descriptor is used to specify both
		*    system-wide conditional access management information such as EMMs and
		*    elementary stream-specific information such as ECMs"
		*    [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace CA_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 0x09;
			TSSI_MTD((R16<2>),
				CA_system_ID);
			TSSI_MTD((MS<R16<4>, 0x1fff, 0>),
				CA_PID);

			// private_data_bytes
		}
		/*******/

		/****h* tssi::iso138181/ISO_639_language_descriptor
		*  NAME
		*    ISO_639_language_descriptor -- "The ISO_639_language_descriptor is used to specify
		*    the language of the associated program element" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace ISO_639_language_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 10;

			inline size_t N(gsl::span<const char> data) noexcept { return descriptor_length(data) >> 2; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R24<2, 4>),
				ISO_639_language_code);
			TSSI_MTD((R8<2 + 3, 4>),
				audio_type);
			// }
		}
		/*******/

		/****h* tssi::iso138181/system_clock_descriptor
		*  NAME
		*    system_clock_descriptor -- "[The system_clock_descriptor] conveys information
		*    about the system clock that was used to generate the timestamps"
		*    [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace system_clock_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 11;

			TSSI_MTD((R1<2, 7>),
				external_clock_reference_indicator);
			TSSI_MTD((MS<R8<2>, 0x3f, 0>),
				clock_accuracy_integer);
			TSSI_MTD((MS<R8<3>, 0xe0, 5>),
				clock_accuracy_exponent);
		}
		/*******/

		/****h* tssi::iso138181/multiplex_buffer_utilization_descriptor
		*  NAME
		*    multiplex_buffer_utilization_descriptor -- "The
		*    multiplex_buffer_utilization_descriptor provides bounds on the occupancy of the
		*    STD multiplex buffer. This information is intended for devices such as
		*    remultiplexers" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace multiplex_buffer_utilization_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 12;

			TSSI_MTD((R1<2, 7>),
				bound_valid_flag);
			TSSI_MTD((MS<R16<2>, 0x7fff, 0>),
				LTW_offset_lower_bound);
			TSSI_MTD((MS<R16<4>, 0x7fff, 0>),
				LTW_offset_upper_bound);
		}
		/*******/

		/****h* tssi::iso138181/copyright_descriptor
		*  NAME
		*    copyright_descriptor -- "The copyright_descriptor provides a method to enable
		*    audio-visual works identification. " [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace copyright_descriptor {
			using namespace descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 13;
			TSSI_MTD((R32<2>),
				copyright_identifier);
			TSSI_MTD((DAT<6, descriptor_length_t, -4>),
				additional_copyright_info);
		}
		/*******/

		/****h* tssi::iso138181/maximum_bitrate_descriptor
		*  NAME
		*    maximum_bitrate_descriptor -- "The value indicates an upper bound of the
		*    bitrate, including transport overhead, that will be encountered in this program
		*    element or program." [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace maximum_bitrate_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 14;
			TSSI_MTD((MS<R24<2>, 0x3fffff, 0>),
				maximum_bitrate);
		}
		/*******/

		/****h* tssi::iso138181/private_data_indicator_descriptor
		*  NAME
		*    private_data_indicator_descriptor -- "Private and shall not be defined by [...]
		*    ISO/IEC" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace private_data_indicator_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 15;
			TSSI_MTD((R32<2>),
				private_data_indicator);
		}
		/*******/

		/****h* tssi::iso138181/smoothing_buffer_descriptor
		*  NAME
		*    smoothing_buffer_descriptor -- "[The smoothing_buffer_descriptor] is optional
		*    and conveys information about the size of a smoothing buffer associated with this
		*    descriptor, and the associated leak rate out of that buffer, for the program
		*    element(s) that it refers to" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace smoothing_buffer_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 16;
			TSSI_MTD((MS<R24<2>, 0x3fffff, 0>),
				sb_leak_rate);
			TSSI_MTD((MS<R24<5>, 0x3fffff, 0>),
				sb_size);
		}
		/*******/

		/****h* tssi::iso138181/STD_descriptor
		*  NAME
		*    STD_descriptor -- "[The STD_descriptor] is optional and applies only to the T-STD
		*    model and to video elementary streams" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace STD_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 17;
			TSSI_MTD((R1<2, 0>),
				leak_valid_flag);
		}
		/*******/

		/****h* tssi::iso138181/IBP_descriptor
		*  NAME
		*    IBP_descriptor -- "[The IBP_descriptor] provides information about some
		*    characteristics of the sequence of frame types in the video sequence"
		*    [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace IBP_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 18;
			TSSI_MTD((R1<2, 7>),
				closed_gop_flag);
			TSSI_MTD((R1<2, 6>),
				identical_gop_flag);
			TSSI_MTD((MS<R16<2>, 0x3fff, 0>),
				max_gop_length);
		}
		/*******/

		/****h* tssi::iso138181/MPEG_4_video_descriptor
		*  NAME
		*    MPEG_4_video_descriptor -- "For individual ISO/IEC 14496-2 streams directly
		*    carried in PES packets the MPEG_4_video_descriptor provides basic information
		*    for identifying the coding parameters of such visual elementary streams. The
		*    MPEG_4_video_descriptor does not apply to ISO/IEC 14496-2 streams encapsulated
		*    in SL-packets and in FlexMux packets" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace MPEG_4_video_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 27;
			TSSI_MTD((R8<2>),
				MPEG_4_visual_profile_and_level);
		}
		/*******/

		/****h* tssi::iso138181/MPEG_4_audio_descriptor
		*  NAME
		*    MPEG_4_audio_descriptor -- "For individual ISO/IEC 14496-3 streams directly
		*    carried in PES packets the MPEG_4_audio_descriptor provides basic information
		*    for identifying the coding parameters of such visual elementary streams. The
		*    MPEG_4_audio_descriptor does not apply to ISO/IEC 14496-3 streams encapsulated
		*    in SL-packets and in FlexMux packets" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace MPEG_4_audio_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 28;
			TSSI_MTD((R8<2>),
				MPEG_4_audio_profile_and_level);
		}
		/*******/

		/****h* tssi::iso138181/IOD_descriptor
		*  NAME
		*    IOD_descriptor -- "The IOD_descriptor encapsulates the InitialObjectDescriptor
		*    namespaceure. An initial object descriptor allows access to a set of ISO/IEC 14496
		*    stream" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace IOD_descriptor {
			using namespace descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 29;
			TSSI_MTD((R8<2>),
				Scope_of_IOD_label);
			TSSI_MTD((R8<3>),
				IOD_label);
			TSSI_MTD((DAT<4, descriptor_length_t, -2>),
				InitialObjectDescriptor);
		}
		/*******/

		/****h* tssi::iso138181/SL_descriptor
		*  NAME
		*    SL_descriptor -- "The SL_descriptor shall be used when a single ISO/IEC 14496-1
		*    SL-packetized stream is encapsulated in PES packets"
		*    [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace SL_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 30;
			TSSI_MTD((R16<2>),
				ES_ID);
		}
		/*******/

		/****h* tssi::iso138181/FMC_descriptor
		*  NAME
		*    FMC_descriptor -- "The FMC_descriptor indicates that the ISO/IEC 14496-1 FlexMux
		*    tool has been used to multiplex ISO/IEC 14496-1 SL-packetized streams into a
		*    FlexMux stream before encapsulation in PES packets or ISO/IEC14496_sections"
		*    [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace FMC_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 31;

			inline size_t N(gsl::span<const char> data) noexcept { return descriptor_length(data) / 3; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R16<2 + 0, 3>),
				ES_ID);
			TSSI_MTD((R8<2 + 2, 3>),
				FlexMuxChannel);
			// }
		}
		/*******/

		/****h* tssi::iso138181/External_ES_ID_descriptor
		*  NAME
		*    External_ES_ID_descriptor -- "The External_ES_ID_descriptor assigns an ES_ID,
		*    as defined in ISO/IEC 14496-1, to a program element to which no ES_ID value
		*    has been assigned by other means" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace External_ES_ID_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 32;
			TSSI_MTD((R16<2>),
				External_ES_ID);
		}
		/*******/

		/****h* tssi::iso138181/Muxcode_descriptor
		*  NAME
		*    Muxcode_descriptor -- "The Muxcode_descriptor conveys MuxCodeTableEntry
		*    namespaceures" [ISO/IEC 13818-1, 2nd edition].
		*  TODO
		*    Add ISO 14496-1 content.
		*  SOURCE
		*/
		namespace Muxcode_descriptor {
			using namespace descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 33;

			// for (auto loop : mux_code_table_loop(data)) {
			namespace loop {
				namespace {
					using length_t =
						R8<0>;
				}
				TSSI_MTD((length_t),
					length);
				TSSI_MTD((DAT<1, length_t>),
					MuxCodeTableEntry);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return length(data) + 1; }

			}
			// }

			TSSI_MTD((ITER<DAT<2, descriptor_length_t>, loop::size>),
				mux_code_table_loop);
		}
		/*******/

		/****h* tssi::iso138181/FmxBufferSize_descriptor
		*  NAME
		*    FmxBufferSize_descriptor -- "The FmxBufferSize_descriptor conveys the size of the
		*    FlexMux buffer (FB) for each SL packetized stream multiplexed in a FlexMux stream"
		*    [ISO/IEC 13818-1, 2nd edition].
		*  TODO
		*    Implement ISO 13818-1 + ISO 14496-1 content
		*  SOURCE
		*/
		namespace FmxBufferSize_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 34;
		}
		/*******/

		/****h* tssi::iso138181/MultiplexBuffer_descriptor
		*  NAME
		*    MultiplexBuffer_descriptor -- "The MultiplexBuffer_descriptor conveys the size of
		*    the multiplex buffer, as well as the leak rate at which data is transferred [...]
		*    for a specific [...] program element" [ISO/IEC 13818-1, 2nd edition].
		*  SOURCE
		*/
		namespace MultiplexBuffer_descriptor {
			using namespace descriptor;
			const uint_fast8_t tag = 35;
			TSSI_MTD((R24<2>),
				MB_buffer_size);
			TSSI_MTD((R24<5>),
				TB_leak_rate);
		}
		/*******/

	}

	namespace etsi300468 {


		/****h* tssi::etsi300468/adaptation_field_data_descriptor
		*  NAME
		*    adaptation_field_data_descriptor -- "The adaptation_field_data_descriptor provides
		*    a means of indicating the type of data fields supported within the private data
		*    field of the adaptation field" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace adaptation_field_data_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x70;
			TSSI_MTD((R8<2>),
				adaptation_field_data_identifier);
		}
		/*******/

		/****h* tssi::etsi300468/ancillary_data_descriptor
		*  NAME
		*    ancillary_data_descriptor -- "The ancillary_data_descriptor provides a means of
		*    indicating the presence and the type of ancillary data in audio elementary
		*    streams" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace ancillary_data_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x6b;
			TSSI_MTD((R8<2>),
				ancillary_data_identifier);
		}
		/*******/

		/****h* tssi::etsi300468/announcement_support_descriptor
		*  NAME
		*    announcement_support_descriptor -- "The announcement_support_descriptor identifies
		*    the type of announcements that are supported by the service"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace announcement_support_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x6e;
			TSSI_MTD((R16<2>),
				announcement_support_indicator);

			// for (auto loop : announcement_support_loop(data)) {
			namespace loop {
				TSSI_MTD((MS<R8<0>, 0xf0, 4>),
					announcement_type);
				TSSI_MTD((MS<R8<0>, 0x07, 0>),
					reference_type);
				// if (reference_type == 0x01
				// || reference_type == 0x02
				// || reference_type == 0x03) {
				TSSI_MTD((R16<1>),
					original_network_id);
				TSSI_MTD((R16<3>),
					transport_stream_id);
				TSSI_MTD((R16<5>),
					service_id);
				TSSI_MTD((R8<7>),
					component_tag);
				// }

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { auto r = reference_type(data); if (r == 0x1 || r == 0x2 || r == 0x3) return 8; else return 1; }
			}
			// }

			TSSI_MTD((ITER<DAT<4, descriptor_length_t, -2>, loop::size>),
				announcement_support_loop);
		}
		/*******/

		/****h* tssi::etsi300468/bouquet_name_descriptor
		*  NAME
		*    bouquet_name_descriptor -- "The bouquet_name_descriptor provides the bouquet name
		*    in text form" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace bouquet_name_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x47;

			TSSI_MTD((CHAR<DAT<2, descriptor_length_t>>),
				chars);
		}
		/*******/

		/****h* tssi::etsi300468/CA_identifier_descriptor
		*  NAME
		*    CA_identifier_descriptor -- "The CA_identifier_descriptor indicates whether a
		*    particular bouquet, service or event is associated with a conditional access
		*    system and identifies the CA system type by means of the CA_system_id"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace CA_identifier_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x53;

			inline size_t N(gsl::span<const char> data) noexcept { return descriptor_length(data) >> 1; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R16<2, 2>),
				CA_system_id);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/cell_frequency_link_descriptor
		*  NAME
		*    cell_frequency_link_descriptor -- "The cell_frequency_link_descriptor may be used
		*    in the [network_information_section] that describes a terrestrial network"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace cell_frequency_link_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x6d;

			// for (auto loop : cell_loop(data)) {
			namespace loop {
				namespace {
					using subcell_info_loop_length_t =
						R8<6>;
				}
				TSSI_MTD((R16<0>),
					cell_id);
				TSSI_MTD((R32<2>),
					frequency);
				TSSI_MTD((subcell_info_loop_length_t),
					subcell_info_loop_length);

				inline size_t N(gsl::span<const char> data) noexcept { return subcell_info_loop_length(data) / 5; }

				// for (i = 0; i < N; i++) {
				TSSI_MTD((R8<7, 5>),
					cell_id_extension);
				TSSI_MTD((R32<7 + 1, 5>),
					transposer_frequency);
				// }

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return subcell_info_loop_length(data) + 7; }
			}
			// }

			TSSI_MTD((ITER<DAT<2, descriptor_length_t>, loop::size>),
				cell_loop);
		}
		/*******/

		/****h* tssi::etsi300468/cell_list_descriptor
		*  NAME
		*    cell_list_descriptor -- "The cell_list_descriptor may be used in the
		*    [network_information_section] that describes a terrestrial network. It provides a
		*    list of all cells of the network k about which the NIT sub-table informs"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace cell_list_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x6c;

			// for (auto loop : cell_loop(data)) {
			namespace loop {
				namespace {
					using subcell_info_loop_length_t =
						R8<9>;
				}
				TSSI_MTD((R16<0>),
					cell_id);
				TSSI_MTD((R16<2>),
					cell_latitude);
				TSSI_MTD((R16<4>),
					cell_longitude);
				TSSI_MTD((MS<R16<6>, 0xfff0, 4>),
					cell_extent_of_latitude);
				TSSI_MTD((MS<R16<7>, 0xfff, 0>),
					cell_extent_of_longitude);

				TSSI_MTD((subcell_info_loop_length_t),
					subcell_info_loop_length);

				inline size_t N(gsl::span<const char> data) noexcept { return subcell_info_loop_length(data) >> 3; }

				// for (i = 0; i < N; i++) {
				TSSI_MTD((R8<10 + 0, 8>),
					cell_id_extension);
				TSSI_MTD((R16<10 + 1, 8>),
					subcell_latitude);
				TSSI_MTD((R16<10 + 3, 8>),
					subcell_longitude);
				TSSI_MTD((MS<R16<10 + 5, 8>, 0xfff0, 4>),
					subcell_extent_of_latitude);
				TSSI_MTD((MS<R16<10 + 6, 8>, 0xfff, 0>),
					subcell_extent_of_longitude);
				// }

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return subcell_info_loop_length(data) + 10; }
			}
			// }

			TSSI_MTD((ITER<DAT<2, descriptor_length_t>, loop::size>),
				cell_loop);
		}
		/*******/

		/****h* tssi::etsi300468/component_descriptor
		*  NAME
		*    component_descriptor -- "The component_descriptor identifies the type of component
		*    stream and may be used to provide a text description of the elementary stream"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace component_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x50;
			TSSI_MTD((MS<R8<2>, 0xf0, 4>),
				stream_content_ext);
			TSSI_MTD((MS<R8<2>, 0xf, 0>),
				stream_content);
			TSSI_MTD((R8<3>),
				component_type);
			TSSI_MTD((R8<4>),
				component_tag);
			TSSI_MTD((R24<5>),
				ISO_639_language_code);

			TSSI_MTD((CHAR<DAT<8, descriptor_length_t, -6>>),
				text_chars);
		}
		/*******/

		/****h* tssi::etsi300468/content_descriptor
		*  NAME
		*    content_descriptor -- "The intention of the content_descriptor is to provide
		*    classification information for an event" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace content_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x54;

			inline size_t N(gsl::span<const char> data) noexcept { return descriptor_length(data) >> 1; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((MS<R8<2 + 0, 2>, 0xf0, 4>),
				content_nibble_level_1);
			TSSI_MTD((MS<R8<2 + 0, 2>, 0xf, 0>),
				content_nibble_level_2);
			TSSI_MTD((R8<2 + 1, 2>),
				user_byte);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/country_availability_descriptor
		*  NAME
		*    country_availability_descriptor -- "The [country_availability_descriptor] may
		*    appear twice for each service, once giving a list of countries and/or groups of
		*    countries where the service is intended to be available, and the second giving
		*    a list of countries and/or groups where it is not" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace country_availability_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x49;

			TSSI_MTD((R1<2, 7>),
				country_availability_flag);

			inline size_t N(gsl::span<const char> data) noexcept { return (descriptor_length(data) - 1) / 3; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R24<3, 3>),
				country_code);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/data_broadcast_descriptor
		*  NAME
		*    data_broadcast_descriptor -- "The data_broadcast_descriptor identifies the type of
		*    the data component and may be used to provide a text description of the data
		*    component" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace data_broadcast_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using selector_length_t =
					R8<5>;
				using text_length_t =
					ADD_R8<selector_length_t, 9>;
			}
			const uint_fast8_t tag = 0x64;
			TSSI_MTD((R16<2>),
				data_broadcast_id);
			TSSI_MTD((R8<4>),
				component_tag);
			TSSI_MTD((selector_length_t),
				selector_length);
			TSSI_MTD((DAT<6, selector_length_t>),
				selector_bytes);

			TSSI_MTD((ADD_R24<selector_length_t, 6>),
				ISO_639_language_code);

			TSSI_MTD((text_length_t),
				text_length);
			TSSI_MTD((CHAR<ADD_DAT<selector_length_t, 10, text_length_t>>),
				text_chars);
		}
		/*******/

		/****h* tssi::etsi300468/data_broadcast_id_descriptor
		*  NAME
		*    data_broadcast_id_descriptor -- "The data_broadcast_id_descriptor identifies the
		*    type of the data component" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace data_broadcast_id_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x66;
			TSSI_MTD((R16<2>),
				data_broadcast_id);
			TSSI_MTD((DAT<4, descriptor_length_t, -2>),
				id_selector_bytes);
		}
		/*******/

		/****h* tssi::etsi300468/cable_delivery_system_descriptor
		*  NAME
		*    cable_delivery_system_descriptor
		*  SOURCE
		*/
		namespace cable_delivery_system_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x44;
			TSSI_MTD((BCD<R32<2>, 8>),
				frequency);
			TSSI_MTD((MS<R8<7>, 0xf, 0>),
				FEC_outer);
			TSSI_MTD((R8<8>),
				modulation);
			TSSI_MTD((BCD<MS<R32<9>, 0xfffffff0, 4>, 7>),
				symbol_rate);
			TSSI_MTD((MS<R8<12>, 0xf, 0>),
				FEC_inner);
		}
		/*******/

		/****h* tssi::etsi300468/satellite_delivery_system_descriptor
		*  NAME
		*    satellite_delivery_system_descriptor
		*  SOURCE
		*/
		namespace satellite_delivery_system_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x43;
			TSSI_MTD((BCD<R32<2>, 8>),
				frequency);
			TSSI_MTD((BCD<R16<6>, 4>),
				orbital_position);
			TSSI_MTD((R1<8, 7>),
				west_east_flag);
			TSSI_MTD((MS<R8<8>, 0x60, 5>),
				polarization);
			TSSI_MTD((MS<R8<8>, 0x18, 3>),
				roll_off);
			TSSI_MTD((R1<8, 2>),
				modulation_system);
			TSSI_MTD((MS<R8<8>, 0x3, 0>),
				modulation_type);
			TSSI_MTD((BCD<MS<R32<9>, 0xfffffff0, 4>, 7>),
				symbol_rate);
			TSSI_MTD((MS<R8<12>, 0xf, 0>),
				FEC_inner);
		}
		/*******/

		/****h* tssi::etsi300468/S2_satellite_delivery_system_descriptor
		*  NAME
		*    S2_satellite_delivery_system_descriptor -- "[The
		*    S2_satellite_delivery_system_descriptor] is only required if DVB-S2 is not used in
		*    non backwards compatible broadcast services mode [...]. In non backwards
		*    compatible broadcast services mode the satellite_delivery_system_descriptor is
		*    sufficient" [ETSI EN 300 468 V1.13.1].
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace S2_satellite_delivery_system_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x79;

			TSSI_MTD((R1<2, 7>),
				scrambling_sequence_selector);
			TSSI_MTD((R1<2, 6>),
				multiple_input_stream_flag);
			TSSI_MTD((R1<2, 5>),
				backwards_compatibility_indicator);
		}
		/*******/

		/****h* tssi::etsi300468/terrestrial_delivery_system_descriptor
		*  NAME
		*    terrestrial_delivery_system_descriptor
		*  SOURCE
		*/
		namespace terrestrial_delivery_system_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x5a;

			TSSI_MTD((R32<2>),
				centre_frequency);
			TSSI_MTD((MS<R8<6>, 0xe0, 5>),
				bandwidth);
			TSSI_MTD((R1<6, 4>),
				priority);
			TSSI_MTD((R1<6, 3>),
				Time_Slicing_indicator);
			TSSI_MTD((R1<6, 2>),
				MPE_FEC_indicator);
			TSSI_MTD((MS<R8<7>, 0xc0, 6>),
				constellation);
			TSSI_MTD((MS<R8<7>, 0x38, 3>),
				hierarchy_information);
			TSSI_MTD((MS<R8<7>, 0x7, 0>),
				code_rate_HP_stream);
			TSSI_MTD((MS<R8<8>, 0xe0, 5>),
				code_rate_LP_stream);
			TSSI_MTD((MS<R8<8>, 0x18, 3>),
				guard_interval);
			TSSI_MTD((MS<R8<8>, 0x6, 1>),
				transmission_mode);
			TSSI_MTD((R1<8, 0>),
				other_frequency_flag);
		}
		/*******/

		/****h* tssi::etsi300468/DSNG_descriptor
		*  NAME
		*    DSNG_descriptor -- "In Digital Satellite News Gathering (DSNG) transmissions the
		*    [TS_description_section] (TSDT) shall be present in the bitstream and the TSDT
		*    [descriptors] shall contain the DSNG_descriptor with the ASCII codes for "CONA" in
		*    the text field" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace DSNG_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x68;
			TSSI_MTD((DAT<2, descriptor_length_t>),
				bytes);
		}
		/*******/

		/****h* tssi::etsi300468/extended_event_descriptor
		*  NAME
		*    extended_event_descriptor -- "The extended_event_descriptor provides a detailed
		*    text description of an event, which may be used in addition to the
		*    short_event_descriptor." [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace extended_event_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using length_of_items_t =
					R8<6>;
				using text_length_t =
					ADD_R8<length_of_items_t, 7>;
			}
			const uint_fast8_t tag = 0x4e;

			TSSI_MTD((MS<R8<2>, 0xf0, 4>),
				descriptor_number);
			TSSI_MTD((MS<R8<2>, 0xf, 0>),
				last_descriptor_number);
			TSSI_MTD((R24<3>),
				ISO_639_language_code);

			TSSI_MTD((length_of_items_t),
				length_of_items);

			// for (auto loop : item_loop(data)) {
			namespace loop {
				namespace {
					using item_description_length_t =
						R8<0>;
					using item_length_t =
						ADD_R8<item_description_length_t, 1>;
				}

				TSSI_MTD((item_description_length_t),
					item_description_length);
				TSSI_MTD((CHAR<DAT<1, item_description_length_t>>),
					item_description_chars);

				TSSI_MTD((item_length_t),
					item_length);
				TSSI_MTD((CHAR<ADD_DAT<item_description_length_t, 2, item_length_t>>),
					text_chars);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return item_description_length(data) + item_length(data) + 2; }
			}
			// }	

			TSSI_MTD((ITER<DAT<7, length_of_items_t>, loop::size>),
				item_loop);

			TSSI_MTD((text_length_t),
				text_length);

			TSSI_MTD((CHAR<ADD_DAT<length_of_items_t, 8, text_length_t>>),
				text_chars);
		}
		/*******/

		/****h* tssi::etsi300468/extension_descriptor
		*  NAME
		*    extension_descriptor -- "The extension_descriptor is used to extend the 8-bit
		*    namespace of the descriptor_tag field" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace extension_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x7f;
			TSSI_MTD((R8<2>),
				descriptor_tag_extension);
			// selector_bytes
		}
		/*******/

		/****h* tssi::etsi300468/frequency_list_descriptor
		*  NAME
		*    frequency_list_descriptor -- "[The frequency_list_descriptor] gives the complete
		*    list of additional frequencies for a certain multiplex which is transmitted on
		*    multiple frequencies" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace frequency_list_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x62;
			TSSI_MTD((MS<R8<2>, 0x3, 0>),
				coding_type);

			inline size_t N(gsl::span<const char> data) noexcept { return (descriptor_length(data) - 1) >> 2; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R32<3, 4>),
				centre_frequency);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/FTA_content_management_descriptor
		*  NAME
		*    FTA_content_management_descriptor -- "The FTA_content_management_descriptor
		*    provides a means of defining the content management policy for an item of content
		*    delivered as part of a free-to-air (FTA) DVB Service" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace FTA_content_management_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x7e;
			TSSI_MTD((R1<2, 3>),
				do_not_scramble);
			TSSI_MTD((MS<R8<2>, 0x6, 1>),
				control_remote_access_over_internet);
			TSSI_MTD((R1<2, 0>),
				do_not_apply_revocation);
		}
		/*******/

		/****h* tssi::etsi300468/linkage_descriptor
		*  NAME
		*    linkage_descriptor -- "The linkage_descriptor identifies a service that can be
		*    presented if the consumer requests for additional information related to a
		*    specific entity described by the SI system" [ETSI EN 300 468 V1.13.1].
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace linkage_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x4a;
			TSSI_MTD((R16<2>),
				transport_stream_id);
			TSSI_MTD((R16<4>),
				original_network_id);
			TSSI_MTD((R16<6>),
				service_id);
			TSSI_MTD((R8<8>),
				linkage_type);

			TSSI_MTD((DAT<9, descriptor_length_t, -7>),
				info);
			// if (linkage_type == 0x08) info = {
			namespace mobile_hand_over_info {
				TSSI_MTD((MS<R8<0>, 0xf0, 4>),
					hand_over_type);
				TSSI_MTD((R1<0, 0>),
					origin_type);
				// TODO: complete subnamespace
			}
			// } else if (linkage_type == 0x0D ) info = {
			namespace event_linkage_info {
				TSSI_MTD((R16<0>),
					target_event_id);
				TSSI_MTD((R1<2, 7>),
					target_listed);
				TSSI_MTD((R1<2, 6>),
					event_simulcast);
			}
			// } else if (linkage_type >= 0x0E && linkage_type <= 0x1F) info = {
			namespace extended_event_linkage_info {
				TSSI_MTD((R8<0>),
					loop_length);
				// TODO: complete subnamespace
			};
			// }
		}
		/*******/

		/****h* tssi::etsi300468/local_time_offset_descriptor
		*  NAME
		*    local_time_offset_descriptor -- "The local_time_offset_descriptor may be used in
		*    the [time_offset_section] to describe country specific dynamic changes of the
		*    local time offset relative to UTC" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace local_time_offset_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x58;

			inline size_t N(gsl::span<const char> data) noexcept { return descriptor_length(data) / 13; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R24<2, 13>),
				country_code);
			TSSI_MTD((MS<R8<2 + 3, 13>, 0xfc, 2>),
				country_region_id);
			TSSI_MTD((R1<2 + 3, 0, 13>),
				local_time_offset_polarity);
			TSSI_MTD((BCD<R16<2 + 4, 13>, 4>),
				local_time_offset);
			TSSI_MTD((TIME<R40<2 + 6, 13>>),
				time_of_change);
			TSSI_MTD((BCD<R16<2 + 11, 13>, 4>),
				next_time_offset);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/mosaic_descriptor
		*  NAME
		*    mosaic_descriptor -- "A mosaic component is a collection of different video images
		*    to form a coded video component. The information is organized so that each
		*    specific information when displayed appears on a small area of a screen"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace mosaic_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x51;
			TSSI_MTD((R1<2, 7>),
				mosaic_entry_point);
			TSSI_MTD((MS<R8<2>, 0x70, 4>),
				number_of_horizontal_elementary_cells);
			TSSI_MTD((MS<R8<2>, 0x7, 0>),
				number_of_vertical_elementary_cells);

			// for (auto loop : cell_loop(data)) {
			namespace loop {
				namespace {
					using elementary_cell_field_length_t =
						R8<2>;
				}
				TSSI_MTD((MS<R8<0>, 0xfc, 2>),
					logical_cell_id);
				TSSI_MTD((MS<R8<1>, 0x7, 0>),
					logical_cell_presentation_info);

				TSSI_MTD((elementary_cell_field_length_t),
					elementary_cell_field_length);

				// for (i = 0; i < elementary_cell_field_length; i++) {
				TSSI_MTD((MS<R8<3, 1>, 0x3f, 0>),
					elementary_cell_id);
				// }

				TSSI_MTD((ADD_R8<elementary_cell_field_length_t, 3>),
					cell_linkage_info);

				// if (cell_linkage_info == 0x01) {
				TSSI_MTD((ADD_R16<elementary_cell_field_length_t, 4>),
					bouquet_id);
				// } else if (cell_linkage_info == 0x02 || cell_linkage_info == 0x03 || cell_linkage_info == 0x04) {
				TSSI_MTD((ADD_R16<elementary_cell_field_length_t, 4>),
					original_network_id);
				TSSI_MTD((ADD_R16<elementary_cell_field_length_t, 6>),
					transport_stream_id);
				TSSI_MTD((ADD_R16<elementary_cell_field_length_t, 8>),
					service_id);
				// } 
				// if (cell_linkage_info == 0x04) {
				TSSI_MTD((ADD_R16<elementary_cell_field_length_t, 10>),
					event_id);
				//

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { auto i = cell_linkage_info(data); auto l = elementary_cell_field_length(data);  if (i == 0x1) return l + 6; else if (i == 0x2 || i == 0x3) return l + 10; else if (i == 0x4) return l + 12; else return l + 4; }
			}
			// }	

			TSSI_MTD((ITER<DAT<3, descriptor_length_t, -1>, loop::size>),
				cell_loop);
		}
		/*******/

		/****h* tssi::etsi300468/multilingual_bouquet_name_descriptor
		*  NAME
		*    multilingual_bouquet_name_descriptor -- "The multilingual_bouquet_name_descriptor
		*    provides the bouquet name in text form in one or more languages"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace multilingual_bouquet_name_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x5c;

			// for (auto loop : name_loop(data)) {
			namespace loop {
				namespace {
					using bouquet_name_length_t =
						R8<3>;
				}
				TSSI_MTD((R24<0>),
					ISO_639_language_code);
				TSSI_MTD((bouquet_name_length_t),
					bouquet_name_length);

				TSSI_MTD((CHAR<DAT<4, bouquet_name_length_t>>),
					chars);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return bouquet_name_length(data) + 4; }
			}
			// }

			TSSI_MTD((ITER<DAT<2, descriptor_length_t>, loop::size>),
				name_loop);
		}
		/*******/

		/****h* tssi::etsi300468/multilingual_component_descriptor
		*  NAME
		*    multilingual_component_descriptor -- "The multilingual_component_descriptor
		*    provides a text description of a component in one or more languages"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace multilingual_component_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x5e;
			TSSI_MTD((R8<2>),
				component_tag);

			// for (auto loop : text_loop(data)) {
			namespace loop {
				namespace {
					using text_description_length_t =
						R8<3>;
				}
				TSSI_MTD((R24<0>),
					ISO_639_language_code);
				TSSI_MTD((text_description_length_t),
					text_description_length);

				TSSI_MTD((CHAR<DAT<4, text_description_length_t>>),
					text_chars);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return text_description_length(data) + 4; }
			}
			// }

			TSSI_MTD((ITER<DAT<3, descriptor_length_t, -1>, loop::size>),
				text_loop);
		}
		/*******/

		/****h* tssi::etsi300468/multilingual_network_name_descriptor
		*  NAME
		*    multilingual_network_name_descriptor -- "The multilingual_network_name_descriptor
		*    provides the network name in text form in one or more languages"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace multilingual_network_name_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x5b;

			// for (auto loop : name_loop(data)) {
			namespace loop {
				namespace {
					using network_name_length_t =
						R8<3>;
				}
				TSSI_MTD((R24<0>),
					ISO_639_language_code);

				TSSI_MTD((network_name_length_t),
					network_name_length);

				TSSI_MTD((CHAR<DAT<4, network_name_length_t>>),
					chars);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return network_name_length(data) + 4; }
			}
			// }

			TSSI_MTD((ITER<DAT<2, descriptor_length_t>, loop::size>),
				name_loop);
		}
		/*******/

		/****h* tssi::etsi300468/multilingual_service_name_descriptor
		*  NAME
		*    multilingual_service_name_descriptor -- "The multilingual_service_name_descriptor
		*    provides the names of the service provider and service in text form in one or
		*    more languages" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace multilingual_service_name_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x5d;

			// for (auto loop : name_loop(data)) {
			namespace loop {
				namespace {
					using service_provider_name_length_t =
						R8<3>;
					using service_name_length_t =
						ADD_R8<service_provider_name_length_t, 4>;
				}
				TSSI_MTD((R24<0>),
					ISO_639_language_code);
				TSSI_MTD((service_provider_name_length_t),
					service_provider_name_length);
				TSSI_MTD((CHAR<DAT<4, service_provider_name_length_t>>),
					provider_chars);
				TSSI_MTD((service_name_length_t),
					service_name_length);
				TSSI_MTD((CHAR<ADD_DAT<service_provider_name_length_t, 5, service_name_length_t>>),
					name_chars);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return service_provider_name_length(data) + service_name_length(data) + 5; }
			}
			// }

			TSSI_MTD((ITER<DAT<2, descriptor_length_t>, loop::size>),
				name_loop);
		}
		/*******/

		/****h* tssi::etsi300468/NVOD_reference_descriptor
		*  NAME
		*    NVOD_reference_descriptor -- "The NVOD_reference_descriptor gives a list of the
		*    services which together form a [Near Video On Demand] NVOD service"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace NVOD_reference_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x4b;

			inline size_t N(gsl::span<const char> data) noexcept { return descriptor_length(data) / 6; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R16<2 + 0, 6>),
				transport_stream_id);
			TSSI_MTD((R16<2 + 2, 6>),
				original_network_id);
			TSSI_MTD((R16<2 + 4, 6>),
				service_id);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/network_name_descriptor
		*  NAME
		*    network_name_descriptor -- "The network_name_descriptor provides the network name
		*    in text form" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace network_name_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x40;
			TSSI_MTD((CHAR<DAT<2, descriptor_length_t>>),
				chars);
		}
		/*******/

		/****h* tssi::etsi300468/parental_rating_descriptor
		*  NAME
		*    parental_rating_descriptor -- "[The parental_rating_descriptor] gives a rating
		*    based on age and allows for extensions based on other rating criteria"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace parental_rating_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x55;

			inline size_t N(gsl::span<const char> data) noexcept { return descriptor_length(data) >> 2; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R24<2, 4>),
				country_code);
			TSSI_MTD((R8<2 + 3, 4>),
				rating);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/PDC_descriptor
		*  NAME
		*    PDC_descriptor -- "The PDC_descriptor extends the DVB system with the
		*    functionalities of PDC (EN 300 231)" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace PDC_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x69;

			TSSI_MTD((MS<R32<1>, 0xfffff, 0>),
				programme_identification_label);
		}
		/*******/

		/****h* tssi::etsi300468/private_data_specifier_descriptor
		*  NAME
		*    private_data_specifier_descriptor -- "[The private_data_specifier_descriptor] is
		*    used to identify the specifier of any private descriptors or private fields within
		*    descriptors" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace private_data_specifier_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x5f;

			TSSI_MTD((R32<2>),
				private_data_specifier);
		}
		/*******/

		/****h* tssi::etsi300468/scrambling_descriptor
		*  NAME
		*    scrambling_descriptor -- "The scrambling_descriptor indicates the selected mode of
		*    operation for the scrambling system" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace scrambling_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x65;

			TSSI_MTD((R8<2>),
				scrambling_mode);
		}
		/*******/

		/****h* tssi::etsi300468/service_descriptor
		*  NAME
		*    service_descriptor -- "The service_descriptor provides the names of the service
		*    provider and the service in text form together with the service_type"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace service_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using service_provider_name_length_t =
					R8<3>;
				using service_name_length_t =
					ADD_R8<service_provider_name_length_t, 4>;
			}
			const uint_fast8_t tag = 0x48;
			TSSI_MTD((R8<2>),
				service_type);
			TSSI_MTD((service_provider_name_length_t),
				service_provider_name_length);
			TSSI_MTD((CHAR<DAT<4, service_provider_name_length_t>>),
				provider_chars);
			TSSI_MTD((service_name_length_t),
				service_name_length);
			TSSI_MTD((CHAR<ADD_DAT<service_provider_name_length_t, 5, service_name_length_t>>),
				name_chars);
		}
		/*******/

		/****h* tssi::etsi300468/service_availability_descriptor
		*  NAME
		*    service_availability_descriptor -- "[The service_availability_descriptor] provides
		*    an identification of the cells in which the service is available or not available"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace service_availability_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x72;
			TSSI_MTD((R1<2, 7>),
				availability_flag);

			inline size_t N(gsl::span<const char> data) noexcept { return (descriptor_length(data) - 1) >> 1; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R16<3, 2>),
				cell_id);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/service_list_descriptor
		*  NAME
		*    service_list_descriptor -- "The service_list_descriptor provides a means of
		*    listing the services by service_id and service type" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace service_list_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x41;

			inline size_t N(gsl::span<const char> data) noexcept { return descriptor_length(data) / 3; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R16<2, 3>),
				service_id);
			TSSI_MTD((R8<2 + 2, 3>),
				service_type);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/service_move_descriptor
		*  NAME
		*    service_move_descriptor -- "If it is required to move a service from one TS to
		*    another, a mechanism is provided which enables an IRD to track the service
		*    between TSs by means of a service_move_descriptor" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace service_move_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x60;
			TSSI_MTD((R16<2>),
				new_original_network_id);
			TSSI_MTD((R16<4>),
				new_transport_stream_id);
			TSSI_MTD((R16<6>),
				new_service_id);
		}
		/*******/

		/****h* tssi::etsi300468/short_event_descriptor
		*  NAME
		*    short_event_descriptor -- "The short_event_descriptor provides the name of the
		*    event and a short description of the event in text form"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace short_event_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using event_name_length_t =
					R8<5>;
				using text_length_t =
					ADD_R8<event_name_length_t, 6>;
			}
			const uint_fast8_t tag = 0x4d;
			TSSI_MTD((R24<2>),
				ISO_639_language_code);
			TSSI_MTD((event_name_length_t),
				event_name_length);
			TSSI_MTD((CHAR<DAT<6, event_name_length_t>>),
				event_name_chars);
			TSSI_MTD((text_length_t),
				text_length);
			TSSI_MTD((CHAR<ADD_DAT<event_name_length_t, 7, text_length_t>>),
				text_chars);
		}
		/*******/

		/****h* tssi::etsi300468/short_smoothing_buffer_descriptor
		*  NAME
		*    short_smoothing_buffer_descriptor -- "A smoothing_buffer_descriptor is specified
		*    in [iso138181] which enables the bit-rate of a service to be signalled in the PSI.
		*    For use in DVB SI Tables, a more compact and efficient descriptor, the
		*    short_smoothing_buffer_descriptor, is defined" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace short_smoothing_buffer_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x61;
			TSSI_MTD((MS<R8<2>, 0xc0, 6>),
				sb_size);
			TSSI_MTD((MS<R8<2>, 0x3f, 0>),
				sb_leak_rate);
		}
		/*******/

		/****h* tssi::etsi300468/stream_identifier_descriptor
		*  NAME
		*    stream_identifier_descriptor -- "The stream_identifier_descriptor may be used
		*    in the PSI [TS_program_map_section] to label component streams of a service so
		*    that they can be differentiated" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace stream_identifier_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x52;
			TSSI_MTD((R8<2>),
				component_tag);
		}
		/*******/

		/****h* tssi::etsi300468/stuffing_descriptor
		*  NAME
		*    stuffing_descriptor -- "The stuffing_descriptor provides a means of invalidating
		*    previously coded descriptors or inserting dummy descriptors for table stuffing"
		*    [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace stuffing_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x42;
			// stuffing bytes
		}
		/*******/

		/****h* tssi::etsi300468/subtitling_descriptor
		*  NAME
		*    subtitling_descriptor -- "In the ISO/IEC 13818-1 [TS_program_map_section] (PMT)
		*    the value of stream_type for any PID carrying DVB subtitle shall be "0x06"
		*    (this indicates a PES carrying private data)" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace subtitling_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x59;

			inline size_t N(gsl::span<const char> data) noexcept { return descriptor_length(data) / 3; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R24<2, 8>),
				ISO_639_language_code);
			TSSI_MTD((R8<2 + 1, 8>),
				subtitling_type);
			TSSI_MTD((R16<2 + 4, 8>),
				composition_page_id);
			TSSI_MTD((R16<2 + 6, 8>),
				ancillary_page_id);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/telephone_descriptor
		*  NAME
		*    telephone_descriptor -- "The telephone_descriptor may be used to indicate a
		*    telephone number which may be used in conjunction with a modem (PSTN or cable) to
		*    exploit narrowband interactive channels" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace telephone_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using country_prefix_length_t =
					MS<R8<3>, 0x60, 5>;
				using international_area_code_length_t =
					MS<R8<3>, 0x1c, 2>;
				using operator_code_length_t =
					MS<R8<3>, 0x3, 0>;
				using national_area_code_length_t =
					MS<R8<4>, 0x70, 4>;
				using core_number_length_t =
					MS<R8<4>, 0xf, 0>;
			}
			const uint_fast8_t tag = 0x57;
			TSSI_MTD((R1<2, 5>),
				foreign_availability);
			TSSI_MTD((MS<R8<2>, 0x1f, 0>),
				connection_type);
			TSSI_MTD((country_prefix_length_t),
				country_prefix_length);
			TSSI_MTD((international_area_code_length_t),
				international_area_code_length);
			TSSI_MTD((operator_code_length_t),
				operator_code_length);
			TSSI_MTD((national_area_code_length_t),
				national_area_code_length);
			TSSI_MTD((core_number_length_t),
				core_number_length);

			TSSI_MTD((DAT<5, country_prefix_length_t>),
				country_prefix_chars);

			TSSI_MTD((ADD_DAT<country_prefix_length_t, 5, international_area_code_length_t>),
				international_area_code_chars);

			TSSI_MTD((ADD_DAT<ADD<country_prefix_length_t, international_area_code_length_t>, 5, operator_code_length_t>),
				operator_code_chars);

			TSSI_MTD((ADD_DAT<ADD<ADD<country_prefix_length_t, international_area_code_length_t>, operator_code_length_t>, 5, national_area_code_length_t>),
				national_area_code_chars);

			TSSI_MTD((ADD_DAT<ADD<ADD<ADD<country_prefix_length_t, international_area_code_length_t>, operator_code_length_t>, national_area_code_length_t>, 5, core_number_length_t>),
				core_number_chars);
		}
		/*******/

		/****h* tssi::etsi300468/teletext_descriptor
		*  NAME
		*    teletext_descriptor -- "The teletext_descriptor shall be used in the PSI PMT to
		*    identify streams which carry EBU Teletext data" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace teletext_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x56;

			inline size_t N(gsl::span<const char> data) noexcept { return descriptor_length(data) / 5; }

			// for (i = 0; i < N; i++) {
			TSSI_MTD((R24<2, 5>),
				ISO_639_language_code);
			TSSI_MTD((MS<R8<2 + 3, 5>, 0xf8, 3>),
				teletext_type);
			TSSI_MTD((MS<R8<2 + 3, 5>, 0x7, 0>),
				teletext_magazine_number);
			TSSI_MTD((BCD<R8<2 + 4, 5>, 2>),
				teletext_page_number);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/time_shifted_event_descriptor
		*  NAME
		*    time_shifted_event_descriptor -- "The time_shifted_event_descriptor is used in
		*    place of the short_event_descriptor to indicate an event which is a time shifted
		*    copy of another event" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace time_shifted_event_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x4f;
			TSSI_MTD((R16<2>),
				reference_service_id);
			TSSI_MTD((R16<4>),
				reference_event_id);
		}
		/*******/

		/****h* tssi::etsi300468/time_shifted_service_descriptor
		*  NAME
		*    time_shifted_service_descriptor -- "[The time_shifted_service_descriptor] is used
		*    in place of the service_descriptor to indicate services which are time shifted
		*    copies of other services" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace time_shifted_service_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x4c;
			TSSI_MTD((R16<2>),
				reference_service_id);
		}
		/*******/

		/****h* tssi::etsi300468/transport_stream_descriptor
		*  NAME
		*    transport_stream_descriptor -- "The transport_stream_descriptor, being transmitted
		*    in the [TS_description_section] only, may be used to indicate the compliance of a
		*    transport stream with an MPEG based system, e.g. DVB" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace transport_stream_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x67;
			TSSI_MTD((DAT<2, descriptor_length_t>),
				bytes);
		}
		/*******/

		/****h* tssi::etsi300468/VBI_data_descriptor
		*  NAME
		*    VBI_data_descriptor -- "The VBI_data_descriptor shall be used in the PSI
		*    [TS_program_map_section] of a stream which carries VBI data as defined in
		*    EN 301 775" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace VBI_data_descriptor {
			using namespace iso138181::descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t tag = 0x45;

			// for (auto loop : service_loop(data)) {
			namespace loop {
				TSSI_MTD((R8<0>),
					data_service_id);
				TSSI_MTD((R8<1>),
					data_service_descriptor_length);

				// if (data_service_id  == 0x01 ||
				//		data_service_id == 0x02 ||
				//		data_service_id == 0x04 ||
				//		data_service_id == 0x05 ||
				//		data_service_id == 0x06 ||
				//		data_service_id == 0x07) {
				inline size_t N(gsl::span<const char> data) noexcept { auto i = data_service_id(data); if (i >= 1 && i <= 7 && i != 3) return data_service_descriptor_length(data); else return 0; }
				// for (i = 0; i < N; i++) {
				TSSI_MTD((R1<2, 5, 1>),
					field_parity);
				TSSI_MTD((MS<R8<2, 1>, 0x1f, 0>),
					line_offset);
				// }
				// }

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return data_service_descriptor_length(data) + 2; }
			}
			// }

			TSSI_MTD((ITER<DAT<2, descriptor_length_t>, loop::size>),
				service_loop);
		}
		/*******/

		/****h* tssi::etsi300468/VBI_teletext_descriptor
		*  NAME
		*    VBI_teletext_descriptor -- "The VBI_teletext_descriptor shall be used in the PSI
		*    [TS_program_map_section] to identify streams which carry VBI data as well as EBU
		*    Teletext data" [ETSI EN 300 468 V1.13.1].
		*  SOURCE
		*/
		namespace VBI_teletext_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x46;

			inline size_t N(gsl::span<const char> data) noexcept { return descriptor_length(data) / 5; }
			// for (i = 0; i < N; i++) {
			TSSI_MTD((R24<2, 5>),
				ISO_639_language_code);
			TSSI_MTD((MS<R8<2 + 3, 5>, 0xf8, 3>),
				teletext_type);
			TSSI_MTD((MS<R8<2 + 3, 5>, 0x7, 0>),
				teletext_magazine_number);
			TSSI_MTD((BCD<R8<2 + 4, 5>, 2>),
				teletext_page_number);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/CI_ancillary_data_descriptor
		*  NAME
		*    CI_ancillary_data_descriptor -- "The CI_ancillary_data_descriptor is used to
		*    convey ancillary data used in the connamespaceion of Content Identifiers (CI) in
		*    companion screen applications" [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace CI_ancillary_data_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x14;
			// ancillary data field
		}
		/*******/

		/****h* tssi::etsi300468/CP_descriptor
		*  NAME
		*    CP_descriptor -- "The CP_descriptor is used to specify both system-wide and
		*    specific content protection management information"
		*    [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace CP_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x02;
			TSSI_MTD((R16<3>),
				CP_system_id);
			TSSI_MTD((MS<R16<5>, 0x1fff, 0>),
				CP_PID);
			// private data bytes
		}
		/*******/

		/****h* tssi::etsi300468/CP_identifier_descriptor
		*  NAME
		*    CP_identifier_descriptor -- "The CP_identifier_descriptor indicates whether a
		*    particular bouquet, service or event is associated with a content protection
		*    system or carries information relating to a content protection system (e.g. CP
		*    system metadata or CP system renewability messages)"
		*    [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace CP_identifier_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x03;

			inline size_t N(gsl::span<const char> data) noexcept { return (descriptor_length(data) - 1) >> 1; }
			// for (i = 0; i < N; i++) {
			TSSI_MTD((R16<3, 2>),
				CP_system_id);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/cpcm_delivery_signalling_descriptor
		*  NAME
		*    cpcm_delivery_signalling_descriptor -- "The CPCM delivery signalling descriptor
		*    conveys Usage State Information (USI) for Content Protection/Copy Management
		*    (CPCM) systems" [ETSI EN 300 468, October 2015].
		*  TODO
		*    Implement TS 102 825 content
		*  SOURCE
		*/
		namespace cpcm_delivery_signalling_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x01;
		}
		/*******/

		/****h* tssi::etsi300468/C2_delivery_system_descriptor
		*  NAME
		*    C2_delivery_system_descriptor -- "The C2_delivery_system_descriptor shall be
		*    used in the TS loop of the [network_information_section] (NIT) to describe
		*    DVB-C2 transmissions" [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace C2_delivery_system_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x0d;

			TSSI_MTD((R8<3>),
				plp_id);
			TSSI_MTD((R8<4>),
				data_slice_id);
			TSSI_MTD((R32<5>),
				C2_System_tuning_frequency);
			TSSI_MTD((MS<R8<9>, 0xc0, 6>),
				C2_System_tuning_frequency_type);
			TSSI_MTD((MS<R8<9>, 0x38, 3>),
				active_OFDM_symbol_duration);
			TSSI_MTD((MS<R8<9>, 0x7, 0>),
				guard_interval);
		}
		/*******/

		/****h* tssi::etsi300468/SH_delivery_system_descriptor
		*  NAME
		*    SH_delivery_system_descriptor -- "[The SH_delivery_system_descriptor] is used to
		*    transmit the physical parameters for each DVB-SH [50] signal in the DVB network"
		*    [ETSI EN 300 468, October 2015].
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace SH_delivery_system_descriptor {
			using namespace extension_descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t extension_tag = 0x05;
			TSSI_MTD((MS<R8<3>, 0xf0, 4>),
				diversity_mode);

			// for (auto loop : system_loop(data)) {
			namespace loop {
				TSSI_MTD((R1<0, 7>),
					modulation_type);
				TSSI_MTD((R1<0, 6>),
					interleaver_presence);
				TSSI_MTD((R1<0, 5>),
					interleaver_type);

				// TODO: add missing members

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { auto ip = interleaver_presence(data), it = interleaver_type(data); ptrdiff_t r = 3; if (ip) { if (!it) r += 4; else r += 1; } return r; }
			}
			// }		

			TSSI_MTD((ITER<DAT<4, descriptor_length_t, -2>, loop::size>),
				system_loop);
		}
		/*******/

		/****h* tssi::etsi300468/T2_delivery_system_descriptor
		*  NAME
		*    T2_delivery_system_descriptor -- "The T2_delivery_system_descriptor shall be used
		*    in the TS loop of the [network_information_section] to describe DVB-T2
		*    transmissions according to EN 302 755" [ETSI EN 300 468, October 2015].
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace T2_delivery_system_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x04;

			TSSI_MTD((R8<3>),
				plp_id);
			TSSI_MTD((R16<4>),
				T2_system_id);

			// if (descriptor_length > 4) {
			TSSI_MTD((MS<R8<6>, 0xc0, 6>),
				SISO_MISO);
			TSSI_MTD((MS<R8<6>, 0x3c, 2>),
				bandwidth);
			TSSI_MTD((MS<R8<7>, 0xe0, 5>),
				guard_interval);
			TSSI_MTD((MS<R8<7>, 0x1c, 2>),
				transmission_mode);
			TSSI_MTD((R1<7, 1>),
				other_frequency_flag);
			TSSI_MTD((R1<7, 0>),
				tfs_flag);
			// }
		}
		/*******/

		/****h* tssi::etsi300468/C2_bundle_delivery_system_descriptor
		*  NAME
		*    C2_bundle_delivery_system_descriptor -- "The C2_bundle_delivery_system_descriptor
		*    shall be used in the TS loop of the [network_information_section] (NIT) to
		*    describe DVB-C2 transmissions [...] using channel bundling"
		*    [ETSI EN 300 468, October 2015].
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace C2_bundle_delivery_system_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x16;
		}
		/*******/

		/****h* tssi::etsi300468/S2X_satellite_delivery_system_descriptor
		*  NAME
		*    S2X_satellite_delivery_system_descriptor -- "When DVB-S2X modulation as defined in
		*    EN 302 307-2 is used, the S2X_satellite_delivery_system_descriptor is the only
		*    delivery system descriptor needed" [ETSI EN 300 468, October 2015].
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace S2X_satellite_delivery_system_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x17;
		}
		/*******/

		/****h* tssi::etsi300468/image_icon_descriptor
		*  NAME
		*    image_icon_descriptor -- "The image_icon_descriptor carries inline icon data or a
		*    URL that identifies the location of an icon file" [ETSI EN 300 468, October 2015].
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace image_icon_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x00;

			TSSI_MTD((MS<R8<3>, 0xf0, 4>),
				descriptor_number);
			TSSI_MTD((MS<R8<3>, 0xf, 0>),
				last_descriptor_number);
			TSSI_MTD((MS<R8<4>, 0x7, 0>),
				icon_id);
		}
		/*******/

		/****h* tssi::etsi300468/message_descriptor
		*  NAME
		*    message_descriptor -- "[The message_descriptor] allows broadcasters to provide
		*    receivers with a textual message which the receiver may display to the user at
		*    appropriate times" [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace message_descriptor {
			using namespace extension_descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t extension_tag = 0x08;
			TSSI_MTD((R8<3>),
				message_id);
			TSSI_MTD((R24<4>),
				ISO_639_language_code);

			TSSI_MTD((CHAR<DAT<7, descriptor_length_t, -5>>),
				text_chars);
		}
		/*******/

		/****h* tssi::etsi300468/network_change_notify_descriptor
		*  NAME
		*    network_change_notify_descriptor -- "[The network_change_notify_descriptor] allows
		*    broadcasters to signal network change events to receivers. A network change event
		*    is a single, clearly identifiable change in the network configuration, e.g.
		*    transmission parameters and/or available services, which may require action on the
		*    part of receivers." [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace network_change_notify_descriptor {
			using namespace extension_descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t extension_tag = 0x07;

			// for (auto loop : cell_loop(data)) {
			namespace loop {
				namespace {
					using loop_length_t =
						R8<2>;
				}
				TSSI_MTD((R16<0>),
					cell_id);
				TSSI_MTD((loop_length_t),
					loop_length);

				// for (auto loop : change_loop(data)) {
				namespace loop {
					TSSI_MTD((R8<0>),
						network_change_id);
					TSSI_MTD((R8<1>),
						network_change_version);
					TSSI_MTD((TIME<R40<2>>),
						start_time_of_change);
					TSSI_MTD((DUR<R24<7>>),
						change_duration);
					TSSI_MTD((MS<R8<10>, 0xe0, 5>),
						receiver_category);
					TSSI_MTD((R1<10, 4>),
						invariant_ts_present);
					TSSI_MTD((MS<R8<10>, 0xf, 0>),
						change_type);
					TSSI_MTD((R8<11>),
						message_id);
					// if (invariant_ts_present == 1) {
					TSSI_MTD((R16<12>),
						invariant_ts_tsid);
					TSSI_MTD((R16<14>),
						invariant_ts_onid);
					// }

					inline ptrdiff_t size(gsl::span<const char> data) noexcept { return invariant_ts_present(data) ? 16 : 12; }
				}
				// }

				TSSI_MTD((ITER<DAT<3, loop_length_t>, loop::size>),
					change_loop);

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return loop_length(data) + 3; }
			}
			// }

			TSSI_MTD((ITER<DAT<3, descriptor_length_t, -1>, loop::size>),
				cell_loop);
		}
		/*******/

		/****h* tssi::etsi300468/service_relocated_descriptor
		*  NAME
		*    service_relocated_descriptor -- "If a service has moved from one TS to another, a
		*    mechanism is provided which enables an IRD to track the service at its new
		*    location (for example between TSs) by means of a service_relocated_descriptor"
		*    [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace service_relocated_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x0b;
			TSSI_MTD((R16<3>),
				old_original_network_id);
			TSSI_MTD((R16<5>),
				old_transport_stream_id);
			TSSI_MTD((R16<7>),
				old_service_id);
		}
		/*******/

		/****h* tssi::etsi300468/supplementary_audio_descriptor
		*  NAME
		*    supplementary_audio_descriptor -- "The supplementary_audio_descriptor provides
		*    additional information about the associated audio component"
		*    [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace supplementary_audio_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x06;
			TSSI_MTD((R1<3, 7>),
				mix_type);
			TSSI_MTD((MS<R8<3>, 0x7c, 2>),
				editorial_classification);
			TSSI_MTD((R1<3, 0>),
				language_code_present);

			// if (language_code_present == 1) {
			TSSI_MTD((R24<4>),
				ISO_639_language_code);
			// }

			// private data bytes
		}
		/*******/

		/****h* tssi::etsi300468/target_region_descriptor
		*  NAME
		*    target_region_descriptor -- "The target_region_descriptor identifies a set of
		*    target regions. [...] A target region is a geographical area containing the
		*    intended audience of a broadcast" [ETSI EN 300 468, October 2015].
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace target_region_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x09;
			TSSI_MTD((R24<3>),
				country_code);
		}
		/*******/

		/****h* tssi::etsi300468/target_region_name_descriptor
		*  NAME
		*    target_region_name_descriptor -- "A target region is a geographical area
		*    containing the intended audience of a broadcast. [...] The
		*    target_region_name_descriptor assigns a name to a target region"
		*    [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace target_region_name_descriptor {
			using namespace extension_descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t extension_tag = 0x0a;
			TSSI_MTD((R24<3>),
				country_code);
			TSSI_MTD((R24<6>),
				ISO_639_language_code);

			// for (auto loop : region_loop(data)) {
			namespace loop {
				namespace {
					using region_name_length_t =
						MS<R8<0>, 0x3f, 0>;
				}
				TSSI_MTD((MS<R8<0>, 0xc0, 6>),
					region_depth);
				TSSI_MTD((region_name_length_t),
					region_name_length);

				TSSI_MTD((CHAR<DAT<1, region_name_length_t>>),
					text_chars);

				TSSI_MTD((ADD_R8<region_name_length_t, 1>),
					primary_region_code);
				// if (region_depth >= 2) {
				TSSI_MTD((ADD_R8<region_name_length_t, 2>),
					secondary_region_code);
				// if (region_depth == 3) {
				TSSI_MTD((ADD_R16<region_name_length_t, 3>),
					tertiary_region_code);
				// }
				// }

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { auto l = region_name_length(data), r = region_depth(data); if (r < 2) return 2 + l; else if (r == 2) return 3 + l; else return 5 + l; }
			}
			// }

			TSSI_MTD((ITER<DAT<9, descriptor_length_t, -7>, loop::size>),
				region_loop);
		}
		/*******/

		/****h* tssi::etsi300468/T2MI_descriptor
		*  NAME
		*    T2MI_descriptor -- "The T2MI_descriptor may be used in the PSI
		*    [TS_program_map_section] to identify each PID carrying a single stream of T2-MI
		*    within a DVB transport stream" [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace T2MI_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x11;
			TSSI_MTD((MS<R8<3>, 0x7, 0>),
				t2mi_stream_id);
			TSSI_MTD((MS<R8<4>, 0x7, 0>),
				num_t2mi_streams_minus_one);
			TSSI_MTD((R1<5, 0>),
				pcr_iscr_common_clock_flag);
		}
		/*******/

		/****h* tssi::etsi300468/URI_linkage_descriptor
		*  NAME
		*    URI_linkage_descriptor -- "The URI_linkage_descriptor identifies a resource
		*    obtainable via an IP network" [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace URI_linkage_descriptor {
			using namespace extension_descriptor;
			namespace {
				using uri_length_t =
					R8<4>;
			}
			const uint_fast8_t extension_tag = 0x13;
			TSSI_MTD((R8<3>),
				uri_linkage_type);
			TSSI_MTD((uri_length_t),
				uri_length);
			TSSI_MTD((DAT<5, uri_length_t>),
				uri_chars);

			// if ((uri_linkage_type == 0x00)
			//	|| (uri_linkage_type == 0x01)) {
			TSSI_MTD((ADD_R16<uri_length_t, 5>),
				min_polling_interval);
			// }

			// private data bytes
		}
		/*******/

		/****h* tssi::etsi300468/video_depth_range_descriptor
		*  NAME
		*    video_depth_range_descriptor -- "To assist receivers in optimizing the placement of
		*    graphics, like text or icons, they wish to display on top of planostereoscopic 3D
		*    video, the video_depth_range_descriptor indicates the intended depth range of the
		*    3D video" [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace video_depth_range_descriptor {
			using namespace extension_descriptor;
			namespace {
				using descriptor_length_t =
					R8<1>;
			}
			const uint_fast8_t extension_tag = 0x10;

			// for (auto loop : range_loop(data)) {
			namespace loop {
				TSSI_MTD((R8<0>),
					range_type);
				TSSI_MTD((R8<1>),
					range_length);

				// if (range_type == 0) {
				TSSI_MTD((MS<R16<2>, 0xfff0, 4>),
					video_max_disparity_hint);
				TSSI_MTD((MS<R16<3>, 0xfff, 0>),
					video_min_disparity_hint);
				// }

				inline ptrdiff_t size(gsl::span<const char> data) noexcept { return range_length(data) + 2; }
			}
			// }

			TSSI_MTD((ITER<DAT<3, descriptor_length_t, -1>, loop::size>),
				range_loop);
		}
		/*******/

		/****h* tssi::etsi300468/partial_transport_stream_descriptor
		*  NAME
		*    partial_transport_stream_descriptor -- "The [descriptors] of the SIT contains all
		*    the information required for controlling and managing the play-out and copying of
		*    partial TSs. The partial_transport_stream_descriptor is proposed to describe this
		*    information" [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace partial_transport_stream_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x63;
			TSSI_MTD((MS<R32<1>, 0x3fffff, 0>),
				peak_rate);
			TSSI_MTD((MS<R32<4>, 0x3fffff, 0>),
				minimum_overall_smoothing_rate);
			TSSI_MTD((MS<R16<8>, 0x3fff, 0>),
				maximum_overall_smoothing_buffer);
		}
		/*******/

		/****h* tssi::etsi300468/AC_3_descriptor
		*  NAME
		*    AC_3_descriptor -- "The AC_3_descriptor is used in the PSI
		*    [TS_program_map_section] to identify streams which carry AC-3 audio"
		*    [ETSI EN 300 468, October 2015].
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace AC_3_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x6a;
			TSSI_MTD((R1<2, 7>),
				component_type_flag);
			TSSI_MTD((R1<2, 6>),
				bsid_flag);
			TSSI_MTD((R1<2, 5>),
				mainid_flag);
			TSSI_MTD((R1<2, 4>),
				asvc_flag);
		}
		/*******/

		/****h* tssi::etsi300468/enhanced_ac_3_descriptor
		*  NAME
		*    enhanced_ac_3_descriptor -- "The enhanced_ac_3_descriptor is used in the PSI
		*    [TS_program_map_section] to identify streams which carry Enhanced AC-3 audio"
		*    [ETSI EN 300 468, October 2015].
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace enhanced_ac_3_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x7a;
			TSSI_MTD((R1<2, 7>),
				component_type_flag);
			TSSI_MTD((R1<2, 6>),
				bsid_flag);
			TSSI_MTD((R1<2, 5>),
				mainid_flag);
			TSSI_MTD((R1<2, 4>),
				asvc_flag);
			TSSI_MTD((R1<2, 3>),
				mixinfoexists);
			TSSI_MTD((R1<2, 2>),
				substream1_flag);
			TSSI_MTD((R1<2, 1>),
				substream2_flag);
			TSSI_MTD((R1<2, 0>),
				substream3_flag);
		}
		/*******/

		/****h* tssi::etsi300468/ac_4_descriptor
		*  NAME
		*    ac_4_descriptor -- "The ac_4_descriptor is used in the PSI
		*    [TS_program_map_section] to identify streams which carry AC-4 audio"
		*    [ETSI EN 300 468, October 2015].
		*  TODO
		*    Implement missing members
		*  SOURCE
		*/
		namespace ac_4_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x15;

		}
		/*******/

		/****h* tssi::etsi300468/DTS_audio_stream_descriptor
		*  NAME
		*    DTS_audio_stream_descriptor -- "The DTS_audio_stream_descriptor is used in the PSI
		*    [TS_program_map_section] to identify streams which carry DTS(R) audio"
		*    [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace DTS_audio_stream_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x7b;
			TSSI_MTD((MS<R8<2>, 0xf0, 4>),
				sample_rate_code);
			TSSI_MTD((MS<R16<2>, 0xfc0, 6>),
				bit_rate_code);
			TSSI_MTD((MS<R16<3>, 0x3f80, 7>),
				nblks);
			TSSI_MTD((MS<R16<4>, 0x7ffe, 1>),
				fsize);
			TSSI_MTD((MS<R16<5>, 0x1f8, 3>),
				surround_mode);
			TSSI_MTD((R1<6, 2>),
				lfe_flag);
			TSSI_MTD((MS<R8<6>, 0x3, 0>),
				extended_surround_flag);

			// additional info bytes
		}
		/*******/

		/****h* tssi::etsi300468/DTS_HD_audio_stream_descriptor
		*  NAME
		*    DTS_HD_audio_stream_descriptor
		*  TODO
		*    add asset info()
		*  SOURCE
		*/
		namespace DTS_HD_audio_stream_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x0e;

			TSSI_MTD((R1<3, 7>),
				substream_core_flag);
			TSSI_MTD((R1<3, 6>),
				substream_0_flag);
			TSSI_MTD((R1<3, 5>),
				substream_1_flag);
			TSSI_MTD((R1<3, 4>),
				substream_2_flag);
			TSSI_MTD((R1<3, 3>),
				substream_3_flag);

			// if (substream_core_flag == 1 ||
			//	   substream_0_flag == 1 ||
			//	   substream_1_flag == 1 ||
			//	   substream_2_flag == 1 ||
			//	   substream_3_flag == 1) {
			TSSI_MTD((R8<4>),
				substream_length);
			TSSI_MTD((MS<R8<5>, 0xe0, 5>),
				num_assets);
			TSSI_MTD((MS<R8<5>, 0x1f, 0>),
				channel_count);
			TSSI_MTD((R1<6, 7>),
				LFE_flag);
			TSSI_MTD((MS<R8<6>, 0x78, 3>),
				sampling_frequency);
			TSSI_MTD((R1<6, 2>),
				sample_resolution);

			// asset_info()

			// }
		}
		/*******/

		/****h* tssi::etsi300468/AAC_descriptor
		*  NAME
		*    AAC_descriptor -- "The AAC_descriptor identifies an AAC coded audio elementary
		*    stream that has been coded in accordance with ISO/IEC 14496-3"
		*    [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace AAC_descriptor {
			using namespace iso138181::descriptor;
			const uint_fast8_t tag = 0x7c;

			TSSI_MTD((R8<2>),
				profile_and_level);

			// if (descriptor_length > 1) {
			TSSI_MTD((R1<3, 7>),
				AAC_type_flag);
			TSSI_MTD((R1<3, 6>),
				SAOC_DE_flag);
			// if (AAC_type_flag == 1) {
			TSSI_MTD((R8<4>),
				AAC_type);
			// }
			// additional info bytes
			// }
		}
		/*******/

		/****h* tssi::etsi300468/DTS_Neural_descriptor
		*  NAME
		*    DTS_Neural_descriptor -- "The DTS_Neural descriptor is used in the
		*    [TS_program_map_section] to identify which audio streams have been processed with
		*    DTS Neural Surround(TM) encoding" [ETSI EN 300 468, October 2015].
		*  SOURCE
		*/
		namespace DTS_Neural_descriptor {
			using namespace extension_descriptor;
			const uint_fast8_t extension_tag = 0x0f;
			TSSI_MTD((R8<3>),
				config_id);

			// additional info bytes
		}
		/*******/

	}


}
