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

#include "ffmpeg_raii_helper.hpp"

namespace sdl {

	extern "C" {

#include "SDL.h"

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

		class SDL_init : noncopyable { // scope important! 
			int init_res;
		public:
			SDL_init() noexcept {	
				static bool initialized = false;
				static int r = 0;
				if (!initialized) {
					initialized = true;
					r = ::sdl::SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO);
				}
				init_res = r;
			}
			int get() const { return init_res; }

			virtual ~SDL_init() {
				::sdl::SDL_Quit();
			}
			 
		};

		class SDL_Window : noncopyable {
		public:
			typedef ::sdl::SDL_Window* type_;

			SDL_Window(const std::string& title, int x, int y, int w, int h, Uint32 flags) noexcept {
				window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
			}

			type_& get() noexcept { return window; }
			const type_& get() const noexcept { return window; }

			virtual ~SDL_Window() {
				if (window != NULL)
					SDL_DestroyWindow(window);
			}

		private:
			type_ window;
		};

		class SDL_Renderer : noncopyable {
		public:
			typedef ::sdl::SDL_Renderer* type_;

			SDL_Renderer(const SDL_Window& window, int index, Uint32 flags) {
				if (window.get())
				renderer = SDL_CreateRenderer(window.get(), index, flags);
				else
					renderer = NULL;
			}

			type_& get() noexcept { return renderer; }
			const type_& get() const noexcept { return renderer; }

			virtual ~SDL_Renderer() {
				if (renderer != NULL)
					SDL_DestroyRenderer(renderer);
			}

		private:
			type_ renderer;
		};

		template<Uint32 pixel_format>
		class SDL_Texture : noncopyable {
		public:
			typedef ::sdl::SDL_Texture* type_;

			SDL_Texture(const SDL_Renderer& renderer, int width, int height) noexcept : width(width), height(height) {
				texture = SDL_CreateTexture(renderer.get(), pixel_format, SDL_TEXTUREACCESS_STREAMING, width, height);
			}

			SDL_Texture(const SDL_Renderer& renderer) noexcept :
				width(0),
				height(0),
				renderer(renderer),
				texture(0) { }

			type_& get() noexcept { return texture; }
			const type_& get() const noexcept { return texture; }

			bool write_frame(const ffmpeg::oop::AVFrame& frame) {
				if (!renderer.get()) 
					return false;
				

				if (!texture) {
					// create output texture
					width = frame.get()->linesize[0];//>width;
					height = frame.get()->height;
					texture = SDL_CreateTexture(renderer.get(), pixel_format, SDL_TEXTUREACCESS_STREAMING, width, height);
				}
				else {
					if ((width != frame.get()->linesize[0]) || (height != frame.get()->height)) {
						// the output texture is incompatible
						SDL_DestroyTexture(texture);
						width = frame.get()->linesize[0]; //width;
						height = frame.get()->height;
						texture = SDL_CreateTexture(renderer.get(), pixel_format, SDL_TEXTUREACCESS_STREAMING, width, height);
					}
				}

				if (!texture) {
					return false;
				}

				// texture is okay
				uint8_t* pixels = nullptr;
				int pitch = 0;
				if (SDL_LockTexture(texture, nullptr, (void**)&pixels, &pitch) != 0) {
					destroy();
					return false;
				}

				if (frame.get()->linesize[0] != pitch) {
					// copy line by line
					for (const auto i : { 0, 2, 1 }) {
						int line_size = std::min(frame.get()->linesize[i], pitch);
						for (int y = 0; y < height; y++) {
							memcpy(pixels + y * pitch, frame.get()->data[i] + y * frame.get()->linesize[i], line_size);
						}
						pixels += pitch * height;
						if (i == 0) {
							pitch >>= 1;
							height >>= 1;
						}
					}
				}
				else {
					// copy block-wise
					int frame_size = pitch * height;
					memcpy(pixels, frame.get()->data[0], frame_size);
					pixels += frame_size;
					memcpy(pixels, frame.get()->data[2], frame_size >> 2);
					pixels += frame_size >> 2;
					memcpy(pixels, frame.get()->data[1], frame_size >> 2);
				}



				SDL_UnlockTexture(texture);
				return true;
			}

			void destroy() {
				if (texture)
					SDL_DestroyTexture(texture);
				texture = 0;
			}

			virtual ~SDL_Texture() {
				destroy();
			}

		private:
			int width;
			int height;
			const SDL_Renderer& renderer;
			type_ texture;
		};


	}

}