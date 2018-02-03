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

#include <gsl/span>
#include <utility>

namespace ffmpeg {

	extern "C" {

#include "libavcodec\avcodec.h"
#include "libavutil\imgutils.h"
#include "libswscale\swscale.h"

	}
	
	namespace oop {


		class noncopyable {
		public:
			noncopyable() = default;
			~noncopyable() = default;

		private:
			noncopyable(const noncopyable& other) = delete; // non construction-copyable
			noncopyable& operator=(const noncopyable&) = delete; // non copyable		
		};

		class AVCodec { // copyable
		public:
			typedef ::ffmpeg::AVCodec* type_;
			
			AVCodec(AVCodecID id) noexcept {
				codec = avcodec_find_decoder(id);
			}
			AVCodec(const AVCodec& other) = default; //  construction-copyable
			AVCodec& operator=(const AVCodec&) = default; //  copyable	

			type_& get() noexcept { return codec; }
			const type_& get() const noexcept { return codec; }

			virtual ~AVCodec() { /* nothing to destruct here */ }

		private:
			type_ codec;
		};

		class AVDictionary : noncopyable {
		public:
			typedef ::ffmpeg::AVDictionary* type_;

			AVDictionary() noexcept : dictionary(NULL) { }

			type_& get() noexcept { return dictionary; }
			const type_& get() const noexcept { return dictionary; }

			virtual ~AVDictionary() { 
				if (dictionary != NULL)
					av_dict_free(&dictionary); 
			}

		private:
			type_ dictionary;
		};


		class AVPacket : noncopyable {
		public:
			typedef ::ffmpeg::AVPacket type_;

			type_& get() noexcept { return packet; }
			const type_& get() const noexcept { return packet; }

			AVPacket& operator=(AVPacket&& other)
			{
				std::swap(packet, other.packet);
				return *this;
			}
			AVPacket(AVPacket&& other)
			{
				packet = other.packet;
				other.packet = { 0 };
			}

			AVPacket(gsl::span<const char> data) noexcept : packet{ 0 } {
				const int size = static_cast<int>(data.size());

				uint8_t* av_data = (uint8_t*)av_malloc(size + AV_INPUT_BUFFER_PADDING_SIZE);
				std::copy(data.begin(), data.end(), av_data);
				packet.buf = av_buffer_create(av_data, size + AV_INPUT_BUFFER_PADDING_SIZE,
					av_buffer_default_free, NULL, 0);

				if (!packet.buf)
					return;

				packet.data = av_data;
				packet.size = size;


			}

			virtual ~AVPacket() {

				av_packet_unref(&packet);

			}

		private:
			type_ packet;
		};


		class AVFrame : noncopyable {
		public:
			typedef ::ffmpeg::AVFrame* type_;

			AVFrame() noexcept {
				frame = av_frame_alloc();
				
			}

			type_& get() noexcept { return frame; }
			const type_& get() const noexcept { return frame; }

			AVFrame& operator=(AVFrame&& other)
			{
				//std::swap(frame, other.frame);
				frame = other.frame;
				other.frame = NULL;
				return *this;
			}
			AVFrame(AVFrame&& other)
			{
				frame = other.frame;
				other.frame = NULL;
			}

			virtual ~AVFrame() {
				if (frame != NULL) {
					av_frame_unref(frame);
					av_frame_free(&frame);
				}
			}

		private:
			type_ frame;
		};

		class AVCodecContext : noncopyable {
		public:
			typedef ::ffmpeg::AVCodecContext* type_;

			AVCodecContext(const AVCodec& codec) : codec(codec) {
				if (codec.get() != NULL)
					context = avcodec_alloc_context3(codec.get());
				else
					context = NULL;
			}

			int avcodec_open2(AVDictionary& dictionary) {
				if (context)
					return ::ffmpeg::avcodec_open2(context, codec.get(), &(dictionary.get()));
				else
					return -1;
			}

			int send_packet(const AVPacket& packet) {
				return avcodec_send_packet(context, &(packet.get()));
			}

			std::pair<AVFrame, int> receive_frame() {
				AVFrame frame; 
				int result = avcodec_receive_frame(context, frame.get());
				return std::make_pair(std::move(frame), result);
			}

			type_& get() noexcept { return context; }
			const type_& get() const noexcept { return context; }

			virtual ~AVCodecContext() {
				if (context != NULL) {
					avcodec_free_context(&context);
				}
			}

		private:
			type_ context;
			const AVCodec& codec;
		};



		template<AVPixelFormat dst_format> // AV_PIX_FMT_RGB24
		class SwsContext : noncopyable {
		public:
			typedef ::ffmpeg::SwsContext* type_;

			SwsContext() : sws_ctx(NULL), sws_state(0, 0, AV_PIX_FMT_NONE) {
				
			}

			bool sws_scale(const AVFrame& original, AVFrame& color_scaled) {
				if (!original.get() || !color_scaled.get())
					return false;

				int width = original.get()->width;
				int height = original.get()->height;
				AVPixelFormat src_fmt = (AVPixelFormat) original.get()->format;

				// no context
				if (sws_ctx == NULL) {
					sws_ctx = sws_getContext(width, height, src_fmt, width, height, dst_format, SWS_BILINEAR, 0, 0, 0);
					sws_state = std::make_tuple(width, height, src_fmt);
				}

				// wrong context
				if (sws_state != std::make_tuple(width, height, src_fmt)) {
					sws_freeContext(sws_ctx);
					sws_ctx = sws_getContext(width, height, src_fmt, width, height, dst_format, SWS_BILINEAR, 0, 0, 0);
					sws_state = std::make_tuple(width, height, src_fmt);
				}

				// wrong output
				if (std::make_tuple(width, height, dst_format) != std::make_tuple(color_scaled.get()->width, color_scaled.get()->height, color_scaled.get()->format)) {
					color_scaled.get()->width = width;
					color_scaled.get()->height = height;
					color_scaled.get()->format = dst_format;
					av_freep(&color_scaled.get()->data[0]);
					av_image_alloc(color_scaled.get()->data, color_scaled.get()->linesize, width, height, dst_format, 32);

				}
				
				auto result_height = ::ffmpeg::sws_scale(
					sws_ctx,
					original.get()->data,
					original.get()->linesize,
					0,
					height,
					color_scaled.get()->data,
					color_scaled.get()->linesize);

				return height == result_height;

			}

			type_& get() noexcept { return sws_ctx; }
			const type_& get() const noexcept { return sws_ctx; }

			virtual ~SwsContext() {
				sws_freeContext(sws_ctx);
			}

		private:
			type_ sws_ctx;
			std::tuple<int, int, AVPixelFormat> sws_state; // width, height, src format
		};

	}

}