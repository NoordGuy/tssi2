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
using namespace tssi;

struct html_shell {
	html_shell(ofstream& _f) : f(_f) {
		// write header
		f << u8"<html><head>" << endl;
		f << u8"<title>tssi PSI example</title>" << endl;
		f << u8"<link rel=\"stylesheet\" href=\"report.css\">" << endl;
		f << u8"</head><body>" << endl;
		f << u8"<h1>tssi PSI data report example</h1>" << endl;
		f << u8"<h2>file: examples/data/ard.ts</h2>" << endl;
		f << u8"<hr />" << endl;
	}
	~html_shell() {
		// write footer
		f << u8"</body></html>" << endl;
	}

private:
	ofstream& f;
};

struct html_row {
	html_row(ofstream& _f) : f(_f) {}
	void row(string label, string value) { f << u8"<tr><td></td><td>" << label << u8"</td><td>" << value << u8"</td>" << endl; }
	void row_major(string label, string value) { f << u8"<tr><td colspan=\"2\">" << label << u8"</td><td>" << value << u8"</td>" << endl; }

	void row(string label, char value) { row(label, to_string(static_cast<int>(static_cast<unsigned char>(value)))); }
	void row_major(string label, char value) { row_major(label, to_string(static_cast<int>(static_cast<unsigned char>(value)))); }
	void row(string label, int value) { row(label, to_string(value)); }
	void row_major(string label, int value) { row_major(label, to_string(value)); }
	void row(string label, uint_fast32_t value) { row(label, to_string(value)); }
	void row_major(string label, uint_fast32_t value) { row_major(label, to_string(value)); }
private:
	ofstream& f;
};

struct html_table : html_row{
	html_table(ofstream& _f, string caption) : f(_f), html_row(_f) {
		f << u8"<h3>" << caption << u8"</h3>" << endl;
		f << u8"<table><thead><tr><th colspan=\"2\">Member</th><th>Value</th></tr></thead><tbody>" << endl;
	}
	~html_table() {
		f << u8"</tbody></table>";
		f << u8"<hr />" << endl;
	}
private:
	ofstream& f;
};

string ISO639_2_string(uint_fast32_t code) {
	return { static_cast<char>((code & 0xff0000) >> 16), static_cast<char>((code & 0xff00) >> 8), static_cast<char>(code & 0xff) };
}

void write_descriptors(ofstream& f, range_span<descriptor_loop::size> range)
{
	using namespace iso138181;
	using namespace etsi300468;

	html_row r(f);

	// iterate through descriptor list
	for (auto data : range) {		

		switch (descriptor::descriptor_tag(data)) {
		case short_event_descriptor::tag: {
			using namespace short_event_descriptor;
			if (event_name_length(data) > 0)
				r.row(u8"event_name_chars[" + ISO639_2_string(ISO_639_language_code(data)) + u8"]", event_name_chars(data).second);
			if (text_length(data) > 0)
				r.row(u8"text_chars[" + ISO639_2_string(ISO_639_language_code(data)) + u8"]", text_chars(data).second);
			break;
		}
		case extended_event_descriptor::tag: {
			using namespace extended_event_descriptor;
			if (text_length(data) > 0)
				r.row(u8"extended text[" + ISO639_2_string(ISO_639_language_code(data)) + u8"]", text_chars(data).second);
			break;
		}
		case component_descriptor::tag: {
			using namespace component_descriptor;
			r.row(u8"stream_content", stream_content(data));
			r.row(u8"component_type", component_type(data));
			r.row(u8"component_tag", component_tag(data));
			r.row(u8"component text[" + ISO639_2_string(ISO_639_language_code(data)) + u8"]", text_chars(data).second);
			break;
		}
		case PDC_descriptor::tag: {
			using namespace PDC_descriptor;
			r.row(u8"programme_identification_label", programme_identification_label(data));
			break;
		}
		case private_data_specifier_descriptor::tag: {
			using namespace private_data_specifier_descriptor;
			r.row(u8"private_data_specifier", private_data_specifier(data));
			break;
		}
		case content_descriptor::tag: {
			using namespace content_descriptor;
			for (auto i = 0; i < N(data); ++i) {
				r.row(u8"content_nibble", u8"level_1: " +
					to_string(static_cast<int>(static_cast<unsigned char>(content_nibble_level_1(data, i)))) + u8" level_2: " +
					to_string(static_cast<int>(static_cast<unsigned char>(content_nibble_level_2(data, i)))));
			}
			break;
		}
		case linkage_descriptor::tag: {
			using namespace linkage_descriptor;
			r.row(u8"linkage service", u8"TS " + to_string(transport_stream_id(data)) +
				u8" service_id " + to_string(service_id(data)) +
				u8", linkage_type: " + to_string(linkage_type(data)));
			break;
		}
		case satellite_delivery_system_descriptor::tag: {
			using namespace satellite_delivery_system_descriptor;
			r.row(u8"satellite delivery", u8"freq " + to_string(frequency(data)) +
				u8" position " + to_string(orbital_position(data)) +
				u8" east? " + to_string(west_east_flag(data)) +
				u8" h/v " + to_string(polarization(data)) +
				u8" symb " + to_string(symbol_rate(data)) +
				u8" dvb-s2 " + to_string(modulation_system(data)));
			break;
		}
		case network_name_descriptor::tag: {
			using namespace network_name_descriptor;
			r.row(u8"network_name_descriptor", chars(data).second);
			break;
		}
		case bouquet_name_descriptor::tag: {
			using namespace bouquet_name_descriptor;
			r.row(u8"bouquet_name_descriptor", chars(data).second);
			break;
		}
		case country_availability_descriptor::tag: {
			using namespace country_availability_descriptor;
			string caption = u8"country_availability";
			if (!country_availability_flag(data))
				caption = u8"country_non_availability";
			string countries;
			for (auto i = 0; i < N(data); ++i)
				countries += ISO639_2_string(country_code(data, i)) + " ";
			r.row(caption, countries);
			break;
		}
		case service_list_descriptor::tag: {
			using namespace service_list_descriptor;
			string services;
			for (auto i = 0; i < N(data); ++i)
				services += to_string(service_id(data, i)) + " ";
			r.row(u8"service_list", services);
			break;
		}
		case service_descriptor::tag: {
			using namespace service_descriptor;
			r.row(u8"service_type", service_type(data));
			r.row(u8"name", name_chars(data).second + u8" (" + provider_chars(data).second + u8")");
			break;
		}
		case stream_identifier_descriptor::tag: {
			using namespace stream_identifier_descriptor;
			r.row(u8"component_tag", component_tag(data));
			break;
		}
		case data_broadcast_descriptor::tag: {
			using namespace data_broadcast_descriptor;
			string bytes;
			for (auto i = 0; i < selector_bytes(data).size(); ++i)
				bytes += to_string(static_cast<int>(static_cast<unsigned char>(selector_bytes(data)[i]))) + " ";
			r.row(u8"data_broadcast_id", to_string(data_broadcast_id(data)) + u8" ( " + bytes + u8")");
			r.row(u8"component_tag", component_tag(data));
			r.row(u8"broadcast id text[" + ISO639_2_string(ISO_639_language_code(data)) + u8"]", text_chars(data).second);
			break;
		}
		case data_broadcast_id_descriptor::tag: {
			using namespace data_broadcast_id_descriptor;
			string bytes;
			for (auto i = 0; i < id_selector_bytes(data).size(); ++i)
				bytes += to_string(static_cast<int>(static_cast<unsigned char>(id_selector_bytes(data)[i]))) + " ";
			r.row(u8"data_broadcast_id", to_string(data_broadcast_id(data)) + u8" ( " + bytes + u8")");
			break;
		}
		case ISO_639_language_descriptor::tag: {
			using namespace ISO_639_language_descriptor;
			for (auto i = 0; i < N(data); ++i) {
				r.row(u8"audio_type[" + ISO639_2_string(ISO_639_language_code(data, i)) + u8"]", audio_type(data, i));
			}
			break;
		}
		case teletext_descriptor::tag: {
			using namespace teletext_descriptor;
			for (auto i = 0; i < N(data); ++i) {
				r.row(u8"teletext_type[" + ISO639_2_string(ISO_639_language_code(data, i)) + u8"]", teletext_type(data, i));
				r.row(u8"teletext page[" + ISO639_2_string(ISO_639_language_code(data, i)) + u8"]",
					(teletext_magazine_number(data, i) == 0 ? 8 : teletext_magazine_number(data, i)) * 100 + teletext_page_number(data, i));
			}
			break;
		}
		case local_time_offset_descriptor::tag: {
			using namespace local_time_offset_descriptor;
			for (auto i = 0; i < N(data); ++i) {
				r.row(u8"country_code", ISO639_2_string(country_code(data, i)));
				r.row(u8"country_region_id", country_region_id(data, i));
				r.row(u8"local_time_offset_polarity", local_time_offset_polarity(data, i));
				r.row(u8"local_time_offset", local_time_offset(data, i));
				auto time_of_change_ = time_of_change(data, i);
				r.row(u8"time_of_change", ctime(&time_of_change_));
				r.row(u8"next_time_offset", next_time_offset(data, i));
			}
			break;
		}

		case 0xff:
			r.row(u8"forbidden descriptor", u8"0xff");
			break;

		default: {
			using namespace descriptor;
			if (descriptor_tag(data) >= 19 && descriptor_tag(data) <= 26)
				r.row("ISO 13818-6 descriptor", descriptor_tag(data));
			else if (descriptor_tag(data) >= 0x80)
				r.row("private descriptor", descriptor_tag(data));
			else
				r.row("unhandled descriptor", descriptor_tag(data));
		}

		}
		
	}

}



void write_pat(ofstream& f, const map<section_identifier, PSISection<>>& heap)
{

	html_table t(f, u8"Program Association Table (PAT)");
	using namespace iso138181::program_association_section;

	for (auto& v : heap) {
		if (get<0>(v.first) == 0x00) { // table id
			if (v.second.crc32()) {
				auto data = v.second.psi_data();

				t.row_major(u8"transport_stream_id", transport_stream_id(data));

				for (auto i = 0; i < N(data); ++i) {
					t.row(u8"entry # " + to_string(i), 
						u8"program_number: " + to_string(program_number(data, i)) + 
						u8" program_map_PID: " + to_string(program_map_PID(data, i)));
				}
			}
		}
	}
	
}


void write_nit(ofstream& f, const map<section_identifier, PSISection<>>& heap)
{
	html_table t(f, u8"Network Information Table (NIT)");
	using namespace etsi300468::network_information_section;

	for (auto& v : heap) {
		if (get<0>(v.first) == 0x40 || get<0>(v.first) == 0x41) { // table id
			if (v.second.crc32()) {
				// get section data
				auto data = v.second.psi_data();

				// print html rows
				t.row_major(u8"table_id", table_id(data));
				t.row_major(u8"network_id", network_id(data));
				write_descriptors(f, descriptors(data));


				// program info loop
				for (auto loop : transport_stream_loop(data)) {

					t.row(u8"transport_stream_id", loop::transport_stream_id(loop));
					t.row(u8"original_network_id", loop::original_network_id(loop));
					write_descriptors(f, loop::descriptors(loop));
				}
			}
		}
	}
}

void write_bat(ofstream& f, const map<section_identifier, PSISection<>>& heap)
{
	html_table t(f, u8"Bouquet Association Table (BAT)");
	using namespace etsi300468::bouquet_association_section;

	for (auto& v : heap) {
		if (get<0>(v.first) == 0x4a) { // table id
			if (v.second.crc32()) {
				// get section data
				auto data = v.second.psi_data();

				// print html rows
				t.row_major(u8"bouquet_id", bouquet_id(data));
				write_descriptors(f, descriptors(data));

				// program info loop
				for (auto loop : transport_stream_loop(data)) {

					t.row(u8"transport_stream_id", loop::transport_stream_id(loop));
					t.row(u8"original_network_id", loop::original_network_id(loop));
					write_descriptors(f, loop::descriptors(loop));

				}
			}
		}
	}
}


void write_sdt(ofstream& f, const map<section_identifier, PSISection<>>& heap)
{
	html_table t(f, u8"Service Description Table (SDT)");
	using namespace etsi300468::service_description_section;

	for (auto& v : heap) {
		if (get<0>(v.first) == 0x42 || get<0>(v.first) == 0x46) { // table id
			if (v.second.crc32()) {
				// get section data
				auto data = v.second.psi_data();

				// print html rows
				t.row_major(u8"table_id", table_id(data));
				t.row_major(u8"transport_stream_id", transport_stream_id(data));
				t.row_major(u8"original_network_id", original_network_id(data));

				// service info loop
				for (auto loop : service_info_loop(data)) {
					using namespace loop;
					
					t.row(u8"service_id", service_id(loop));
					t.row(u8"EIT_schedule_flag", EIT_schedule_flag(loop));
					t.row(u8"EIT_present_following_flag", EIT_present_following_flag(loop));
					t.row(u8"running_status", running_status(loop));
					t.row(u8"free_CA_mode", free_CA_mode(loop));
					write_descriptors(f, descriptors(loop));

				}
			}
		}
	}
}

void write_pmt(ofstream& f, const map<section_identifier, PSISection<>>& heap)
{
	html_table t(f, u8"Program Map Table (PMT)");
	using namespace iso138181::TS_program_map_section;

	for (auto& v : heap) {
		if (get<0>(v.first) == 0x02) { // table id
			if (v.second.crc32()) {
				// get section data
				auto data = v.second.psi_data();
				
				// print html rows
				t.row_major(u8"program_number", program_number(data));
				t.row(u8"PCR_PID", PCR_PID(data));
				write_descriptors(f, descriptors(data));

				// program info loop
				for (auto loop : program_info_loop(data)) {

					t.row(u8"stream_type", loop::stream_type(loop));
					t.row(u8"elementary_PID", loop::elementary_PID(loop));
					write_descriptors(f, loop::descriptors(loop));
				}
			}
		}
	}
}

void write_tsdt(ofstream& f, const map<section_identifier, PSISection<>>& heap)
{
	html_table t(f, u8"Transport Stream Description Table (TSDT)");
	using namespace iso138181::TS_description_section;

	for (auto& v : heap) {
		if (get<0>(v.first) == 0x03) { // table id
			if (v.second.crc32()) {
				// get section data
				auto data = v.second.psi_data();

				write_descriptors(f, descriptors(data));
			}
		}
	}
}

void write_tdt(ofstream& f, const map<section_identifier, PSISection<>>& heap)
{
	html_table t(f, u8"Time Date Table (TDT)");
	using namespace etsi300468::time_date_section;

	for (auto& v : heap) {
		if (get<0>(v.first) == 0x70) { // table id
			
			// get section data
			auto data = v.second.psi_data();

			auto start_time = UTC_time(data);
			t.row_major(u8"UTC_time", ctime(&start_time));
						
		}
	}
}


void write_tot(ofstream& f, const map<section_identifier, PSISection<>>& heap)
{
	html_table t(f, u8"Time Offset Table (TOT)");
	using namespace etsi300468::time_offset_section;

	for (auto& v : heap) {
		if (get<0>(v.first) == 0x73) { // table id

			// get section data
			auto data = v.second.psi_data();

			auto start_time = UTC_time(data);
			t.row_major(u8"UTC_time", ctime(&start_time));
			write_descriptors(f, descriptors(data));
		}
	}
}

void write_rst(ofstream& f, const map<section_identifier, PSISection<>>& heap)
{
	html_table t(f, u8"Running Status Table (RST)");
	using namespace etsi300468::running_status_section;

	for (auto& v : heap) {
		if (get<0>(v.first) == 0x71) { // table id

			// get section data
			auto data = v.second.psi_data();

			for (auto i = 0; i < N(data); ++i) {
				t.row_major(u8"transport_stream_id", transport_stream_id(data, i));
				t.row_major(u8"original_network_id", original_network_id(data, i));
				t.row_major(u8"service_id", service_id(data, i));
				t.row(u8"event_id", event_id(data, i));
				t.row(u8"running_status", running_status(data, i));
			}

		}
	}
}

void write_eit(ofstream& f, const map<section_identifier, PSISection<>>& heap, bool small_table)
{
	html_table t(f, u8"Event information table (EIT)");
	using namespace etsi300468::event_information_section;

	for (auto& v : heap) {
		if (get<0>(v.first) >= 0x4e && get<0>(v.first) <= 0x6f) { // table id
			if (small_table && get<0>(v.first) != 0x4e) // only p/f on small print out
				continue;
			if (v.second.crc32()) {
				// get data of the whole section
				auto data = v.second.psi_data();

				// print table rows...
				t.row_major(u8"table_id", table_id(data));
				t.row_major(u8"service_id", service_id(data));

				// print event loop
				for (auto loop : event_info_loop(data)) {
					using namespace loop;

					// print futher rows per event
					t.row(u8"event_id", event_id(loop));
					auto start_time_ = start_time(loop);
					t.row(u8"start_time", ctime(&start_time_));
					t.row(u8"duration", to_string(chrono::duration_cast<chrono::minutes> (duration(loop)).count()) + u8"min");
					t.row(u8"running_status", running_status(loop));
					t.row(u8"free_CA_mode", free_CA_mode(loop));
					write_descriptors(f, descriptors(loop));
				}
			}
		}
	}
	
}



int main() {

	// change tssi global string handling to "html"
	tssi::string_reader<>::emphasis_on("<b>");
	tssi::string_reader<>::emphasis_off("</b>");
	tssi::string_reader<>::linebreak("<br/>");

	ifstream file_ts("examples/data/ard.ts", ifstream::binary);

	if (file_ts.fail()) {
		cout << "Could not open examples/data/ard.ts." << endl;
		return 1;
	}

	ofstream file_html("examples/psidata/report.html");

	if (file_html.fail()) {
		cout << "Could not write to file examples/psidata/report.html." << endl;
		return 1;
	}

	// write UTF-8 BOM
	// tssi uses UTF-8, too
	unsigned char bom[] = { 0xEF,0xBB,0xBF };
	file_html.write((char*)bom, sizeof(bom));

	// write html head (and footer)
	html_shell _no_need_for_a_name(file_html);

	// read buffer
	const size_t buffer_size = 1048576;
	auto buffer = vector<char>(buffer_size);

	// the ts parser
	TSParser<> parser;
	// we need a psi storage, too
	PSIHeap<> heap;
	auto& psi_data = heap.psi_heap();

	// add PIDs for PAT, PMT TSDT, NIT, BAT, SDT, TDT, TOT, RST, EIT, ...
	parser.pid_parser({ 0x00, 0x01, 0x02, 0x10, 0x11, 0x12, 0x13, 0x14 }, heap);

	// add PMTs via callback
	heap.psi_callback([&](const tssi::section_identifier si) {
		if (get<0>(si) != 0x00) // check for PMT
			return;
				
		using namespace iso138181::program_association_section;
	
		// PAT -> PMT
		auto data = psi_data.at(si).psi_data();
		for (size_t i = 0; i < N(data); ++i) {
			parser.pid_parser({ program_map_PID(data, i) }, heap);
		}
	});

	// read transport stream
	while (file_ts.good()) {
		file_ts.read(buffer.data(), buffer.size());

		if (file_ts.gcount() == buffer_size)
			parser(buffer);
	}


	// write report
	write_pat(file_html, psi_data);
	write_pmt(file_html, psi_data);
	write_tsdt(file_html, psi_data);

	write_nit(file_html, psi_data);
	write_bat(file_html, psi_data);
	write_sdt(file_html, psi_data);
	write_tdt(file_html, psi_data);
	write_tot(file_html, psi_data);
	write_rst(file_html, psi_data);

	write_eit(file_html, psi_data, true);
	
	return 0;
}