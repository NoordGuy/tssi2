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

/*
	                                                                               _________     __________
																				  |         |   |          |
	                                                                              | ffmpeg  |   |   sdl    |
	                                                             /===============>|  Video  |==>|  Video   |
	                                                             |                | Decoder |   | Renderer |
	                                                             |                |---------|   |----------|
	___________      ________              ___________           |   ________      _________     __________
	\          \    |        |PID 401     |           |PID 401   |  |        |    |         |   |          |  
 	/ C++ in-  /    |   TS   |===========>|    PES    |==========/  |  Audio |    | ffmpeg  |   |   sdl    |
	\ put file \===>| Parser |            | Assembler |             | Parser |===>|  Audio  |==>|  Audio   |
	/ stream   /    |        |PID 402     |           |PID 402      |        |    | Decoder |   | Renderer |
	\__________\    |--------|===========>|-----------|============>|--------|    |---------|   |----------|
		
*/


#include <fstream>
#include <iostream>
#include <deque>

#include <mutex>
#include <condition_variable>
#include <atomic>

#include "ffmpeg_raii_helper.hpp"
#include "sdl_raii_helper.hpp"

#include "tsparser.hpp"
#include "mpegaudio.hpp"
#include "specifications.hpp"

using namespace std;
using namespace gsl;

class sdl_renderer : sdl::oop::SDL_init {
	sdl::oop::SDL_Window window;
	sdl::oop::SDL_Renderer renderer;
	sdl::oop::SDL_Texture<sdl::SDL_PIXELFORMAT_YV12> texture;
	sdl::SDL_AudioDeviceID audio_device;

	deque<ffmpeg::oop::AVFrame> render_list;
	mutex render_mutex;

	atomic<int64_t> last_queued_audio_pts;
	mutex audio_mutex;
	deque<ffmpeg::oop::AVFrame> audio_list;
	int buffer_position;
	sdl::SDL_AudioSpec current_audio_spec;

public:

	sdl_renderer(string title) : 
		window(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 768, 576, sdl::SDL_WINDOW_RESIZABLE),
		renderer(window, -1, sdl::SDL_RENDERER_ACCELERATED | sdl::SDL_RENDERER_PRESENTVSYNC),
		texture(renderer),
		last_queued_audio_pts(-1),
		buffer_position(0)
		{

		if (SDL_init::get() != 0) {
			cout << "Cannot initialize sdl." << endl;
			return;
		}
		if (!window.get()) {
			cout << "Cannot create sdl window." << endl;
			return;
		}
		if (!renderer.get()) {
			cout << "Cannot create sdl renderer." << endl;
			return;
		}

		// create audio device
		audio_device = 0;
		sdl::SDL_AudioSpec want = { 0 };

		// assume something reasonable
		want.freq = 48000;
		want.format = AUDIO_S16LSB;
		want.channels = 2;
		want.callback = SDL_AudioCallback;
		want.userdata = (void*) this;
		want.samples = 512;
		audio_device = sdl::SDL_OpenAudioDevice(NULL, 0, &want, &current_audio_spec, 0);

		if (audio_device < 2) {
			cout << "Cannot create audio device." << endl;
			return;
		}

		// start playback
		sdl::SDL_PauseAudioDevice(audio_device, 0);


	}

	virtual ~sdl_renderer() {
		if (audio_device >= 2)
			sdl::SDL_CloseAudioDevice(audio_device);
	}



	static void SDL_AudioCallback(void* userdata, sdl::Uint8* stream, int len) {
		sdl_renderer * self = static_cast<sdl_renderer*>(userdata);
		
		// retrieve len bytes from audio_list

		int64_t pts = -1;

		unique_lock<std::mutex> guard(self->audio_mutex);

		

		int bytes_todo = len;
		while (!self->audio_list.empty() && bytes_todo) {
			if (bytes_todo == len) {
				// the current avframe carries the pts we are going to use
				pts = self->audio_list.front().get()->pts;
				auto bytes_per_sample = self->current_audio_spec.size / self->current_audio_spec.samples;
				pts += (static_cast<int64_t>(self->buffer_position) * 90000) / (self->current_audio_spec.freq * bytes_per_sample);

				
			}

			if (self->buffer_position + bytes_todo <= self->audio_list.front().get()->linesize[0]) {
				// we can complete the buffer with this run
				copy(self->audio_list.front().get()->data[0] + self->buffer_position, self->audio_list.front().get()->data[0] + self->buffer_position + bytes_todo, &stream[len - bytes_todo]);

				self->buffer_position += bytes_todo;
				bytes_todo = 0;
				if (self->buffer_position == self->audio_list.front().get()->linesize[0]) {
					// pop front
					self->audio_list.pop_front();
					self->buffer_position = 0;
				}
			}
			else {
				// process till the end of the frame
				copy(self->audio_list.front().get()->data[0] + self->buffer_position, self->audio_list.front().get()->data[0] + self->audio_list.front().get()->linesize[0], &stream[len - bytes_todo]);

				bytes_todo -= self->audio_list.front().get()->linesize[0] - self->buffer_position;
				self->buffer_position = 0;				
				self->audio_list.pop_front();

			}
		}
		guard.unlock();

		if (bytes_todo) {
			// fill silence
			memset(&stream[len - bytes_todo], 0, bytes_todo);
		}
		self->last_queued_audio_pts = pts;

	}


	void resize() {
		sdl::SDL_RenderClear(renderer.get());
		sdl::SDL_RenderPresent(renderer.get());
	}

	bool render() {

		if (last_queued_audio_pts < 0) {
			sdl::SDL_Delay(100);
			return false;
		}
		
		// {
			unique_lock<std::mutex> guard(render_mutex);
			if (render_list.size() == 0)
				return false;

			ffmpeg::oop::AVFrame frame = move(render_list.front());
			render_list.pop_front();

			guard.unlock();
			
		// }

		auto video_pts = frame.get()->pts;
		if (video_pts < last_queued_audio_pts) {
			// fast forward
		}
		else {
			auto delay = (video_pts - last_queued_audio_pts) / 90;
			sdl::SDL_Delay(static_cast<sdl::Uint32>(delay));
		}
		
		auto ready = sdl::SDL_RenderClear(renderer.get());
		if (ready != 0) {
			resize();
			return false;
		}
		else
		{			
			if (!texture.write_frame(frame))
				cout << " CANNOT FILL TEXTURE " << endl;
			sdl::SDL_Rect source_rect;
			source_rect.x = 0;
			source_rect.y = 0;
			source_rect.w = frame.get()->width;
			source_rect.h = frame.get()->height;
			sdl::SDL_RenderCopy(renderer.get(), texture.get(), &source_rect, NULL);
			sdl::SDL_RenderPresent(renderer.get());
		}
		return true;

	}

	void queue_frame(ffmpeg::oop::AVFrame& frame) {
		lock_guard<std::mutex> guard(render_mutex);
		render_list.push_back(std::move(frame));
	}

	bool queue_audio(ffmpeg::oop::AVFrame& frame) {
		if (audio_device >= 2) {
			// check compatibilty

			if ((current_audio_spec.channels != frame.get()->channels) ||
				(current_audio_spec.freq != frame.get()->sample_rate)) {

				sdl::SDL_CloseAudioDevice(audio_device);				

				// create audio device
				sdl::SDL_AudioSpec want = { 0 };
				want.freq = frame.get()->sample_rate;
				want.format = AUDIO_S16LSB;
				want.channels = static_cast<sdl::Uint8>(frame.get()->channels);
				want.callback = SDL_AudioCallback;
				want.userdata = (void*) this;
				want.samples = 512;
				audio_device = sdl::SDL_OpenAudioDevice(NULL, 0, &want, &current_audio_spec, 0);

				// flush buffer
				{
					lock_guard<std::mutex> guard(audio_mutex);
					audio_list.clear();
				}

				// start playback
				sdl::SDL_PauseAudioDevice(audio_device, 0);

			}
		}

		// push back...
		lock_guard<std::mutex> guard(audio_mutex);
		audio_list.push_back(std::move(frame));
		
		return true;
	}

};

class ffmpeg_decoder : ffmpeg::oop::noncopyable {
protected:
	ffmpeg::oop::AVCodec avcodec;
	ffmpeg::oop::AVCodecContext avcodec_ctx;
	ffmpeg::oop::AVDictionary dict;
		
	deque<ffmpeg::oop::AVPacket> input_list;

	sdl_renderer& renderer;

	mutex mutex_;
	condition_variable cv;
	bool stop_;
	thread decoder_thread;

	virtual void receive_frame() = 0;

public:
	ffmpeg_decoder(ffmpeg::AVCodecID avcodec_id, sdl_renderer& renderer, std::function<void (ffmpeg::oop::AVCodecContext&)> context_setup) :
		avcodec(avcodec_id), 
		avcodec_ctx(avcodec) , 
		renderer(renderer), 
		stop_(false) {
		if (!avcodec.get()) {
			cout << "decoder not available." << endl;
			return;
		}
		if (!avcodec_ctx.get()) {
			cout << "decoder setup failed." << endl;
			return;
		}
		context_setup(avcodec_ctx);
		
		if (avcodec_ctx.avcodec_open2(dict) < 0) {
			cout << "Could not open decoder." << endl;
			return;
		}
	}
	
	void queue_packet(span<const char> data, int64_t pts) {
		ffmpeg::oop::AVPacket p(data);
		p.get().pts = pts;
		{			
			lock_guard<std::mutex> guard(mutex_);
			input_list.push_back(std::move(p));
		}
		// notify thread by setting conditional variable
		cv.notify_one();		
	}

	void start() {
		stop_ = false;

		decoder_thread = std::thread([&]() {

			for (;;) {
				
				//{
					unique_lock<std::mutex> mklock(mutex_);
					
					while (!stop_ && input_list.size() == 0)
						cv.wait(mklock);

					if (stop_)
						break;
					
					ffmpeg::oop::AVPacket packet(std::move(input_list.front()));
					input_list.pop_front();

					mklock.unlock();
				//}

				avcodec_ctx.send_packet(packet);
				receive_frame();

			}
		});

	}

	void stop() {
		{
			lock_guard<std::mutex> guard(mutex_);
			stop_ = true;
		}
		cv.notify_one();
		decoder_thread.join();
	}

	void flush() {
		{
			lock_guard<std::mutex> guard(mutex_);
			input_list.clear();
		}
		// notify thread by setting conditional variable
		cv.notify_one();
	}

};

class ffmpeg_video_decoder : public ffmpeg_decoder {
	ffmpeg::oop::SwsContext<ffmpeg::AV_PIX_FMT_YUV420P> yuv_scaler;

	void receive_frame() {
		for (;;) {
			auto decoder_result = avcodec_ctx.receive_frame();

			if (decoder_result.second == 0) {
				const ffmpeg::oop::AVFrame& frame = decoder_result.first;
				if (frame.get()->format != ffmpeg::AV_PIX_FMT_YUV420P) {
					// color scaling
					ffmpeg::oop::AVFrame yuv_frame;
					yuv_scaler.sws_scale(frame, yuv_frame);
					renderer.queue_frame(yuv_frame);
				}
				else {
					// no color scaling necessary
					renderer.queue_frame(decoder_result.first);
				}

			}
			else
				break;
		}
	}

public:

	ffmpeg_video_decoder(ffmpeg::AVCodecID avcodec_id, sdl_renderer& renderer) :
		ffmpeg_decoder(avcodec_id, renderer, [](ffmpeg::oop::AVCodecContext& codec_ctx) { codec_ctx; }) {}
};

class ffmpeg_audio_decoder : public ffmpeg_decoder {
	void receive_frame() {

		for (;;) {
			auto decoder_result = avcodec_ctx.receive_frame();
			if (decoder_result.second == 0) {
				renderer.queue_audio(decoder_result.first);
			}
			else {
				break;
			}
		}
	}

public:
	ffmpeg_audio_decoder(ffmpeg::AVCodecID avcodec_id, sdl_renderer& renderer) :
		ffmpeg_decoder(avcodec_id, renderer, [](ffmpeg::oop::AVCodecContext& codec_ctx){
		// we do not want planar formats
		codec_ctx.get()->request_sample_fmt = ffmpeg::AV_SAMPLE_FMT_S16;
	}) { }
};

// SDL injects its own main function
// and renames this one with a catchy define
extern "C"
int main(int argc, char *argv[])
{
	argc; argv;
	
	ffmpeg::avcodec_register_all();
	sdl_renderer renderer{ u8"tssi2 simple mpeg2 video player" };
	ffmpeg_video_decoder video_decoder{ ffmpeg::AV_CODEC_ID_MPEG2VIDEO, renderer };
	ffmpeg_audio_decoder audio_decoder{ ffmpeg::AV_CODEC_ID_MP3, renderer };
	
	ifstream file_ts("examples/data/ard.ts", ifstream::binary);

	if (file_ts.fail()) {
		cout << "Could not open examples/data/ard.ts." << endl;
		return 1;
	}

	tssi::TSParser<> parser;
	tssi::PESAssembler<> pes_assembler;
	tssi::MPEGAudio<> audio_parser;

	// pid and callback setup
	parser.pid_parser({ 401, 402 }, pes_assembler);
		
	pes_assembler.pes_callback(401, [&](span<const char> data) {
		using namespace tssi::iso138181::PES_packet_media;
		auto es_data = PES_packet_data_bytes(data);
		uint_fast64_t pts = 0;
		if ((PTS_DTS_flags(data) & 0x2) == 0x2)
			pts = PTS(data);
		video_decoder.queue_packet(es_data, pts);
	});

	pes_assembler.pes_callback(402, audio_parser);

	audio_parser.audio_callback([&](span<const char> data) {
		auto pts = audio_parser.audio_pts();
		audio_decoder.queue_packet(data, pts);
	});

	const auto buffer_size = 163840;
	vector<char> buffer;
	buffer.resize(buffer_size); 

	video_decoder.start();
	audio_decoder.start();
	
	atomic<bool> programrunning (true); 
	auto parser_thread = thread([&]() {

		while (file_ts.good() && programrunning) {
			file_ts.read(buffer.data(), buffer.size());
			
			if (file_ts.gcount() == buffer_size)
				parser(buffer);
			sdl::SDL_Delay(20);

		}
	});

	sdl::SDL_Event evt;
	
	while (programrunning)
	{
		// a new sdl event?
		while (sdl::SDL_PollEvent(&evt)) {

			switch (evt.type) {
			case sdl::SDL_QUIT:
				programrunning = false;
				break;
			case sdl::SDL_WINDOWEVENT:
				switch (evt.window.event) {
				case sdl::SDL_WINDOWEVENT_RESIZED:
					{
						renderer.resize();
					}
					break;
				}
			}
		}

		// render a frame
		renderer.render();		
		
	}

	parser_thread.join();
	video_decoder.stop();
	audio_decoder.stop();
	cout << "Program ended." << endl;


	return 0;
}