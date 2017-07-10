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

#include <functional>
#include "span_reader.hpp"

namespace tssi
{

/****t* tssi/callback_t
*  NAME
*    callback_t -- General type of a function to call when new data was assembled
*    and can be processed by another module.
*  DATA SCOPE
*    iso138181::transport_packet, iso138181::PES_packet, 
*    iso138181::private_section,...
*  SYNOPSIS
*/
using callback_t = std::function< void(gsl::span<const char> data) >;
/*******/

/****c* tssi/ProcessNode
*  NAME
*    ProcessNode -- Provides an abstraction layer and debug information for data 
*    restructuring classes.
*  METHODS
*    operator()
*    duration
*    call_count
*    byte_count
*    stat_reset
*****/
class ProcessNode {
protected:
	virtual void process(gsl::span<const char>) = 0;
	
private:
#ifdef DEBUG
	std::chrono::nanoseconds process_duration = 0ns;
	size_t n_calls = 0;
	size_t b_count = 0;
#endif //DEBUG

public:
	//operator callback_t() { return [this](auto data) { this->operator()(data); }; }

	/****m* ProcessNode/operator()
	*  NAME
	*    operator() -- Process a data buffer in the respective derived class.
	*   SYNOPSIS
	*/
	void operator()(gsl::span<const char> data) 
	/*******/
	{
#ifdef DEBUG
		process(data);
		b_count += data.sizechars();
		++n_calls;
		std::chrono::high_resolution_clock::time_point time_start = std::chrono::high_resolution_clock::now();
#endif //DEBUG

		// call
		process(data); 

#ifdef DEBUG
		process_duration += std::chrono::duration_cast<std::chrono::nanoseconds>
			(std::chrono::high_resolution_clock::now() - time_start);
#endif //DEBUG
	}

#ifdef DEBUG
	/****m* ProcessNode/duration
	*  NAME
	*    duration -- Debug function. Returns time spent during data processing in total.
	*   SYNOPSIS
	*/
	std::chrono::nanoseconds duration() const noexcept
	/*******/
	{ return process_duration; }

	/****m* ProcessNode/call_count
	*  NAME
	*    call_count -- Debug function. Returns the absolute number of processing calls this node has received.
	*   SYNOPSIS
	*/
	size_t call_count() const noexcept
	/*******/
	{ return n_calls; }

	/****m* ProcessNode/byte_count
	*  NAME
	*    byte_count -- Debug function. Bytes processed by this ProcessNode in total.
	*   SYNOPSIS
	*/
	size_t byte_count() const noexcept
	/*******/
	{ return b_count; }

	/****m* ProcessNode/stat_reset
	*  NAME
	*    stat_reset -- Debug function. Resets statistics collected by this ProcessNode.
	*   SYNOPSIS
	*/
	void stat_reset() noexcept
	/*******/
	{
		std::chrono::nanoseconds process_duration = 0ns;
		size_t n_calls = 0;
		size_t b_count = 0;
	}
#endif //DEBUG

};

class LambdaNode : public ProcessNode {
public:
	LambdaNode(callback_t callback) :
		callback(callback) { }

	LambdaNode(const LambdaNode& rhs) {
		callback = rhs.callback;
	}

	LambdaNode(LambdaNode&& rhs) {
		std::swap(callback, rhs.callback);
	}

private:
	callback_t callback;

	void process(gsl::span<const char> data) { callback(data); }
};

}

