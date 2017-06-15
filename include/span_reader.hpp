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

#include <gsl/span>
#include <string>
#include <chrono>

namespace tssi
{

template <size_t offset, size_t length>
class basic_reader {
public:
	typedef char element_type;
	static constexpr unsigned char error_value = 0x00;

	element_type operator()(gsl::span<const char> data, size_t index = 0, size_t offset2 = 0) const noexcept
	{
		return at(data, index, offset2);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0, size_t offset2 = 0) noexcept
	{
		const ptrdiff_t position = offset + index * length + offset2;		
		if (position >= data.size())
			return static_cast<element_type>(error_value);
		else
			return data[position];
	}
};

template <size_t offset, class count_reference, ptrdiff_t count_reference_offset, size_t length>
class span_reader {
public:
	typedef gsl::span<const char> element_type;

	element_type operator()(gsl::span<const char> data, size_t index = 0, size_t offset2 = 0) const noexcept
	{
		return at(data, index, offset2);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0, size_t offset2 = 0) noexcept
	{
		const ptrdiff_t ref = static_cast<size_t>(count_reference::at(data, 0)) + count_reference_offset;
		const ptrdiff_t off = offset + index * length + offset2;
		if (off + ref > data.size())
			return data.subspan(data.size());
		else
			return data.subspan(off, ref);
		// index of count_reference always == 0
	}

};

typedef ptrdiff_t(*tssi_size_t)(gsl::span<const char> data);
template<tssi_size_t iteration_stride, bool is_const>
class range_span_iterator {
	typedef gsl::span<const char> Span;
	using element_type = typename Span::element_type;
	using index_type = std::ptrdiff_t;
	using reference = std::conditional_t<is_const, const Span, Span>&;
	using pointer = std::add_pointer_t<reference>;

	static const element_type value = 0;

public:
	constexpr range_span_iterator() : span_(&value, static_cast<index_type>(0)) { }

	constexpr range_span_iterator(const gsl::span<const char> span) noexcept : span_(span) { }

	friend class range_span_iterator<iteration_stride, true>;
	constexpr range_span_iterator(const range_span_iterator<iteration_stride, false>& other) noexcept :
	range_span_iterator(other.span_) { }

	constexpr range_span_iterator(range_span_iterator&&) noexcept = default;

	constexpr range_span_iterator& operator++() noexcept
	{
		// get loop size
		//iteration_stride loop;
		//auto size = loop.size(span_);
		auto size = iteration_stride(span_);

		// go one loop length ahead
		if (size <= span_.length())
			span_ = span_.subspan(size);
		else
			span_ = span_.subspan(span_.size());

		return *this;
	}

	constexpr range_span_iterator operator++(int) noexcept
	{
		auto ret = *this;
		++(*this);
		return ret;
	}

	constexpr reference operator*()  noexcept
	{
		return (span_);
	}

	constexpr reference operator*() const noexcept
	{
		return (span_);
	}

	constexpr pointer operator->() noexcept
	{
		return &(span_);
	}

	constexpr pointer operator->() const noexcept
	{
		return &(span_);
	}

	constexpr friend bool operator==(const range_span_iterator& lhs, const range_span_iterator& rhs) noexcept
	{
		return (lhs.size() == rhs.size()) && lhs.span_ == rhs.span_;
	}

	constexpr friend bool operator!=(const range_span_iterator& lhs, const range_span_iterator& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	constexpr index_type length() const noexcept { return size(); }
	constexpr index_type size() const noexcept { return span_.size(); }
	constexpr index_type lengthchars() const noexcept { return sizechars(); }
	constexpr index_type sizechars() const noexcept { return span_.sizechars(); }
	constexpr bool empty() const noexcept { return size() == 0; }

	void swap(range_span_iterator& rhs)
	{
		std::swap(span_, rhs.span_);
	}

private:
	Span span_;
};

template<tssi_size_t iteration_stride>
class range_span {
	typedef gsl::span<const char> Span;
	using element_type = typename Span::element_type;
	using index_type = std::ptrdiff_t;
	using reference = element_type&;

public:
	using iterator = range_span_iterator<iteration_stride, false>;
	using const_iterator = range_span_iterator<iteration_stride, true>;

	constexpr range_span(Span data) noexcept : data_(data) { }
	constexpr range_span(range_span&&) noexcept = default;

	iterator begin() { return { data_ }; }
	iterator end() { return {}; }

	const_iterator cbegin() { return { data_ }; }
	const_iterator cend() { return {}; }

	constexpr index_type length() const noexcept { return size(); }
	constexpr index_type size() const noexcept { return data_.size(); }
	constexpr index_type lengthchars() const noexcept { return sizechars(); }
	constexpr index_type sizechars() const noexcept { return data_.sizechars(); }
	constexpr bool empty() const noexcept { return size() == 0; }

	constexpr operator Span() const noexcept { return data_; }
	constexpr Span data() const noexcept { return data_; }
	constexpr reference operator[](index_type idx) const noexcept { return _data[idx]; }

	constexpr reference at(index_type idx) const noexcept { return this->operator[](idx); }
	constexpr reference operator()(index_type idx) const noexcept { return this->operator[](idx); }

	constexpr friend bool operator==(const range_span& lhs, const range_span& rhs) noexcept
	{
		return lhs.data_ == rhs.data_;
	}

	constexpr friend bool operator!=(const range_span& lhs, const range_span& rhs) noexcept
	{
		return !(lhs == rhs);
	}

private:
	Span data_;
};

template<class span_reader, tssi_size_t iteration_stride>
class iterable_span {
public:
	typedef range_span<iteration_stride> element_type;

	element_type operator()(gsl::span<const char> data, size_t index = 0) const noexcept
	{
		return at(data, index);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0) noexcept
	{
		return element_type(span_reader::at(data, index));
	}
};

template<class count_reference_a, class count_reference_b>
class reference_sum {
public:
	typedef ptrdiff_t element_type;

	element_type operator()(gsl::span<const char> data, size_t index = 0) const noexcept
	{
		return at(data, index);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0) noexcept
	{
		return static_cast<ptrdiff_t>(count_reference_a::at(data, 0)) + static_cast<ptrdiff_t>(count_reference_b::at(data, 0));
	}

};

template<class count_reference_a, class count_reference_b>
class reference_difference {
public:
	typedef ptrdiff_t element_type;

	element_type operator()(gsl::span<const char> data, size_t index = 0) const noexcept
	{
		return at(data, index);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0) noexcept
	{
		return static_cast<ptrdiff_t>(count_reference_a::at(data, 0)) - static_cast<ptrdiff_t>(count_reference_b::at(data, 0));
	}

};


template <class reader, class shift_reference>
class combined_reader {
public:
	typedef typename reader::element_type element_type;

	element_type operator()(gsl::span<const char> data, size_t index = 0, size_t offset2 = 0) const noexcept
	{
		return at(data, index, offset2);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0, size_t offset2 = 0) noexcept
	{
		return reader::at(data, index, offset2 + shift_reference::at(data, 0));
		// index of shift_reference always == 0
	}
};


template<class reader, size_t position>
class bit_reader {
public:
	typedef bool element_type;

	element_type operator()(gsl::span<const char> data, size_t index = 0) const noexcept
	{
		return at(data, index);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0) noexcept
	{
		return (static_cast<unsigned char>(reader::at(data, index)) & (1 << position));
	}
};


template<class T, class reader, size_t stride = sizeof(T)>
class endian_aware_value_reader {
public:
	typedef T element_type;

	element_type operator()(gsl::span<const char> data, size_t index = 0) const noexcept
	{
		return at(data, index);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0) noexcept
	{
		element_type result{};
		for (auto i = 0; i < stride; ++i)
#ifdef __BIG_ENDIAN
			result += static_cast<T>(static_cast<unsigned char>(reader::at(data, index, i))) << (i << 3);
#else // __BIG_ENDIAN
			result += static_cast<T>(static_cast<unsigned char>(reader::at(data, index, i))) << ((stride - i - 1) << 3);
#endif // __BIG_ENDIAN

		return result;
	}
};

template<class value_reader, uint_fast64_t mask_bits, uint_fast64_t shift_right>
class mask_shift
{
public:
	typedef typename value_reader::element_type element_type;

	element_type operator()(gsl::span<const char> data, size_t index = 0) const noexcept
	{
		return at(data, index);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0) noexcept
	{
		return (value_reader::at(data, index) & static_cast<element_type>(mask_bits)) >> shift_right;
	}

};

template<class value_reader>
class time_convert
{
public:
	typedef time_t element_type;

	element_type operator()(gsl::span<const char> data, size_t index = 0) const
	{
		return at(data, index);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0)
	{
		auto value = value_reader::at(data, index);
		Expects(sizeof(value) >= 8);
		tm t{};

		t.tm_hour = bcd_dec((value & 0xff0000) >> 16);
		t.tm_min = bcd_dec((value & 0xff00) >> 8);
		t.tm_sec = bcd_dec(value & 0xff);

		auto mjd = static_cast<int> (value >> 24);
		auto y1 = static_cast<int> ((mjd - 15078.2) / 365.25);
		auto m1 = static_cast<int> ((mjd - 14956.1 - static_cast<int> (y1 * 365.25)) / 30.6001);
		t.tm_mday = mjd - 14956 - static_cast<int> (y1 * 365.25) - static_cast<int> (m1 * 30.6001);
		auto k = 0;
		if (m1 == 14 || m1 == 15) k = 1;
		t.tm_year = y1 + k;
		t.tm_mon = m1 - 2 - k * 12;

		return mktime(&t); // no-throw guarantee
	}
private:
	static int bcd_dec(uint_fast64_t hex) noexcept {
		if (((hex & 0xf0) >> 4) >= 10)
			return 0;
		if ((hex & 0xf) >= 10)
			return 0;
		return ((hex & 0xf0) >> 4) * 10 + (hex & 0xf);
	}

};

template<class value_reader>
class duration_convert
{
public:
	typedef std::chrono::seconds element_type;

	element_type operator()(gsl::span<const char> data, size_t index = 0) const
	{
		return at(data, index);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0)
	{
		auto value = value_reader::at(data, index);
		Expects(sizeof(value) >= 4);

		element_type result{};

		result += std::chrono::hours(bcd_dec((value & 0xff0000) >> 16));
		result += std::chrono::minutes(bcd_dec((value & 0xff00) >> 8));
		result += std::chrono::seconds(bcd_dec(value & 0xff));

		return result;
	}
private:
	static constexpr int bcd_dec(uint_fast64_t hex) noexcept {
		if (((hex & 0xf0) >> 4) >= 10)
			return 0;
		if ((hex & 0xf) >= 10)
			return 0;
		return ((hex & 0xf0) >> 4) * 10 + (hex & 0xf);
	}

};

template<class value_reader, size_t digits = sizeof(value_reader::element_type) * 2>
class bcd_convert
{
public:
	typedef typename value_reader::element_type element_type;

	element_type operator()(gsl::span<const char> data, size_t index = 0) const noexcept
	{
		return at(data, index);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0) noexcept
	{
		auto value = value_reader::at(data, index);
		element_type result{};
		for (auto i = 0u; i < digits; ++i) {
			result += ((value >> (i << 2)) & 0xf) * ipow(10, i);
		}
		return result;
	}
private:
	static unsigned ipow(unsigned base, unsigned exp) noexcept
	{
		unsigned result = 1;
		while (exp)
		{
			if (exp & 1)
				result *= base;
			exp >>= 1;
			base *= base;
		}

		return result;
	}
};

template<class span_reader = void>
class string_reader
{
public:
	typedef std::pair<bool, std::string> element_type;

private:
	static std::string emphasis_on_char;
	static std::string emphasis_off_char;
	static std::string linebreak_char;

	static constexpr uint_least16_t cp6937_table[256] = {
		// 0	1		2		3		4		5		6		7		8		9		A		B		C		D		E		F 2nd nibble
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // 0 1st nibble
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // 1 
		0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f, // 2
		0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f, // 3
		0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f, // 4
		0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f, // 5
		0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f, // 6
		0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x0000, // 7
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // 8
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // 9
		0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x20ac, 0x00a5, 0x0000, 0x00a7, 0x00a4, 0x2018, 0x201c, 0x00ab, 0x2190, 0x2191, 0x2192, 0x2193, // A
		0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00d7, 0x00b5, 0x00b6, 0x00b7, 0x00f7, 0x2019, 0x201d, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf, // B
		0x0000, 0x0300, 0x0301, 0x0302, 0x0303, 0x0304, 0x0306, 0x0307, 0x0308, 0x0000, 0x030a, 0x0327, 0x0000, 0x030b, 0x0328, 0x030c, // C
		0x2015, 0x00b9, 0x00ae, 0x00a9, 0x2122, 0x266a, 0x00ac, 0x00a6, 0x0000, 0x0000, 0x0000, 0x0000, 0x215b, 0x215c, 0x215d, 0x215e, // D
		0x2126, 0x00c6, 0x0110, 0x00aa, 0x0126, 0x0000, 0x0132, 0x013f, 0x0141, 0x00d8, 0x0152, 0x00ba, 0x00de, 0x0166, 0x014a, 0x0149, // E
		0x0138, 0x00e6, 0x0111, 0x00f0, 0x0127, 0x0131, 0x0133, 0x0140, 0x0142, 0x00f8, 0x0153, 0x00df, 0x00fe, 0x0167, 0x014b, 0x00ad  // F
	};

	static void add_utf8_by_code(const uint_fast32_t cc, std::string& s) {
		if (cc < 0x80) {
			s.push_back(static_cast<char>(cc));
		}
		else
			if (cc < 0x800) {
				s.push_back((cc >> 6) | 0xc0);
				s.push_back((cc & 0x3f) | 0x80);
			}
			else
				if (cc < 0x10000) {
					s.push_back((cc >> 12) | 0xe0);
					s.push_back(((cc >> 6) & 0x3f) | 0x80);
					s.push_back((cc & 0x3f) | 0x80);
				}
				else
					if (cc < 0x110000) {
						s.push_back((cc >> 18) | 0xf0);
						s.push_back(((cc >> 12) & 0x3f) | 0x80);
						s.push_back(((cc >> 6) & 0x3f) | 0x80);
						s.push_back((cc & 0x3f) | 0x80);
					}
	}

	static bool add_special_characters(const uint_fast32_t cc, std::string& s) {
		if (cc == 0x86)
			s += emphasis_on_char;
		else if (cc == 0x87)
			s += emphasis_off_char;
		else if (cc == 0x8a)
			s += linebreak_char;
		else
			return false;
		return true;
	}

	static element_type cp6937(gsl::span<const char> data) {
		std::string s;
		for (auto v : data) {
			unsigned char cc = static_cast<unsigned char> (v);
			if (!add_special_characters(cc, s))
				add_utf8_by_code(cp6937_table[cc], s);
		}
		return std::make_pair(true, s);
	}
	static element_type cp8859_5(gsl::span<const char> data) { return std::make_pair(false, u8"[TODO cp8859_5]"); }
	static element_type cp8859_6(gsl::span<const char> data) { return std::make_pair(false, u8"[TODO cp8859_6]"); }
	static element_type cp8859_7(gsl::span<const char> data) { return std::make_pair(false, u8"[TODO cp8859_7]"); }
	static element_type cp8859_8(gsl::span<const char> data) { return std::make_pair(false, u8"[TODO cp8859_8]"); }
	static element_type cp8859_9(gsl::span<const char> data) {
		std::string s;
		for (auto v : data) {
			uint_fast32_t cc = static_cast<unsigned char> (v);
			if (cc >= 0x20 && cc <= 0x7e)
				add_utf8_by_code(cc, s);
			else if (cc >= 0xa0 && cc <= 0xa9)
				add_utf8_by_code(cc, s);
			else if (cc == 0xaa)
				add_utf8_by_code(0xd7, s);
			else if (cc >= 0xab && cc <= 0xb9)
				add_utf8_by_code(cc, s);
			else if (cc == 0xba)
				add_utf8_by_code(0xf7, s);
			else if (cc >= 0xbb && cc <= 0xcf)
				add_utf8_by_code(cc, s);
			else if (cc == 0xd0)
				add_utf8_by_code(0x011e, s);
			else if (cc >= 0xd1 && cc <= 0xdc)
				add_utf8_by_code(cc, s);
			else if (cc == 0xdd)
				add_utf8_by_code(0x0130, s);
			else if (cc == 0xde)
				add_utf8_by_code(0x015e, s);
			else if (cc >= 0xdf && cc <= 0xef)
				add_utf8_by_code(cc, s);
			else if (cc == 0xf0)
				add_utf8_by_code(0x011f, s);
			else if (cc >= 0xf1 && cc <= 0xfc)
				add_utf8_by_code(cc, s);
			else if (cc == 0xfe)
				add_utf8_by_code(0x015f, s);
			else if (cc == 0xff)
				add_utf8_by_code(cc, s);
			else add_special_characters(cc, s);			
		}
		return std::make_pair(true, s);
	}
	static element_type cp8859_10(gsl::span<const char> data) { return std::make_pair(false, u8"[TODO cp8859_10]"); }
	static element_type cp8859_11(gsl::span<const char> data) { return std::make_pair(false, u8"[TODO cp8859_11]"); }
	static element_type cp8859_13(gsl::span<const char> data) { return std::make_pair(false, u8"[TODO cp8859_13]"); }
	static element_type cp8859_14(gsl::span<const char> data) { return std::make_pair(false, u8"[TODO cp8859_14]"); }
	static element_type cp8859_15(gsl::span<const char> data) { return std::make_pair(false, u8"[TODO cp8859_15]"); }

public:

	element_type operator()(gsl::span<const char> data, size_t index = 0) const
	{
		return at(data, index);
	}

	static element_type at(gsl::span<const char> data, size_t index = 0)
	{
		// is data aligned?
		bool same = is_same<span_reader, void>::value;
		Expects(!same);

		data = span_reader::at(data, index);
		if (data.size() == 0) return std::make_pair(true, "");

		if (static_cast<uint_fast8_t>(data[0]) >= 0x20)
			return cp6937(data); // no identifier

		switch (static_cast<uint_fast8_t>(data[0]))
		{
		case 0x00: return std::make_pair(false, u8"Data error, invalid codepage 0x00.");
		case 0x01: return cp8859_5(data.subspan(1));
		case 0x02: return cp8859_6(data.subspan(1));
		case 0x03: return cp8859_7(data.subspan(1));
		case 0x04: return cp8859_8(data.subspan(1));
		case 0x05: return cp8859_9(data.subspan(1));
		case 0x06: return cp8859_10(data.subspan(1));
		case 0x07: return cp8859_11(data.subspan(1));
			// 0x08 is reserved
		case 0x09: return cp8859_13(data.subspan(1));
		case 0x0a: return cp8859_14(data.subspan(1));
		case 0x0b: return cp8859_15(data.subspan(1));
			// 0x0c to 0x0f reserved
		case 0x10: {
			if (data.size() < 3) return std::make_pair(false, u8"Data error, data length not plausible.");
			if (data[1] != 0) return std::make_pair(false, u8"Reserved codepage, update decoder.");
			switch (static_cast<uint_fast8_t>(data[2]))
			{
				// 0x00 is reserved
			case 0x01: return std::make_pair(false, u8"[cp8859_1 NA]"); // TODO
			case 0x02: return std::make_pair(false, u8"[cp8859_2 NA]"); // TODO
			case 0x03: return std::make_pair(false, u8"[cp8859_3 NA]"); // TODO
			case 0x04: return std::make_pair(false, u8"[cp8859_4 NA]"); // TODO

			case 0x05: return cp8859_5(data.subspan(3));
			case 0x06: return cp8859_6(data.subspan(3));
			case 0x07: return cp8859_7(data.subspan(3));
			case 0x08: return cp8859_8(data.subspan(3));
			case 0x09: return cp8859_9(data.subspan(3));
			case 0x0a: return cp8859_10(data.subspan(3));
			case 0x0b: return cp8859_11(data.subspan(3));
				// 0x0c is reserved
			case 0x0d: return cp8859_13(data.subspan(3));
			case 0x0e: return cp8859_14(data.subspan(3));
			case 0x0f: return cp8859_15(data.subspan(3));
				// 0x10 to 0xff is reserved
			default:
				return std::make_pair(false, u8"Reserved codepage, update decoder.");
			}
		}
		case 0x11: return std::make_pair(false, u8"[Coding 0x11 NA]");
			// The standard does not define the character coding
			// it only states to use the basic multilingual plane 
			// - 16 bit words?
		case 0x12: return std::make_pair(false, u8"[Korean Character Set NA]"); // TODO
		case 0x13: return std::make_pair(false, u8"[Simplified Chinese Characters NA]"); // TODO
		case 0x14: return std::make_pair(false, u8"[Traditional Chinese NA]"); // TODO
		case 0x15: // utf8
			return std::make_pair(true, string(data.data(), data.size()));
			// 0x16 to 0x1e reserved
		case 0x1f: {			
			// company defined encodings
			uint_fast8_t encoding_type_id = data[1];
			return std::make_pair(false, u8"Private codepage " + std::to_string(encoding_type_id) + " not available.");
		}
		default:
			return std::make_pair(false, u8"Reserved codepage, update decoder.");
		}

	}

	static void emphasis_on(std::string utf8) { emphasis_on_char = utf8; }
	static void emphasis_off(std::string utf8) { emphasis_off_char = utf8; }
	static void linebreak(std::string utf8) { linebreak_char = utf8; }

};

template< class span_reader >
std::string string_reader<span_reader>::emphasis_on_char = u8"";
template< class span_reader >
std::string string_reader<span_reader>::emphasis_off_char = u8"";
template< class span_reader >
std::string string_reader<span_reader>::linebreak_char = u8"\n";

}

