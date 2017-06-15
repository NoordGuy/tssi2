# libtssi2

libtssi2 is a header-only library for parsing MPEG-2 and DVB Transport Streams in the domain of multimedia and data processing applications. 

The entire implementation is provided inline in the headers under the include directory. A reference documentation is stored under docs. A modern C++ compiler (C++ 14 / C++ 17) is necessary.

While the main header [include/tsparser.hpp](./include/tsparser.hpp) provides access to the whole library, it is also possible to break out required parts. This comes in handy if you already have a PSI or PES assembler and need some additional tables or descriptors --- in this case just include [include/specifications.hpp](./include/specifications.hpp).

Dependencies:

  - [C++ Guideline Support Library](https://github.com/Microsoft/GSL) (header-only, included; mostly needed for `gsl::span<const T>`, a type just waiting for replacement by `std::array_view<T>` or `std::basic_string_view<T>`)

# License

The GNU General Public License v3 applies to this project. 

If you need another (e.g. commercial) license, [contact me](https://goforcode.com).

# Features

  - Fast
    See [Benchmark](#markdown-header-benchmark)
  - Modern and leak-free [by default](https://www.youtube.com/watch?v=JfmTagWcqoE)
    C++ 14 / C++ 17 / GSL
  - Under active development
    If there has not been an push for a while the next one will happen nevertheless
  - Lightweight
    The library is a few kb in size and header-only.
  - Cross-platform
    Windows, Linux, Mac,... should be supported
  - No-throw
    Transport Streams may be corrupted. libtssi2 is designed to handle data error and not to throw. This is not a no-throw guarantee! Some functions might throw (see the docs). 
  - Multi-threading support
    Reentrant with shared mutual exclusion
  - (To some extent) class-less
    Processing of MPEG and DVB objects by stateless functions. No class overhead.
  - Modular
    Custom data processors can replaced provided processors on any level. Custom allocators are supported as well.

[libtssi1](https://github.com/goforcode-com/libtssi) offers some nice features like ISO 13818-6 handling and will remain available on GitHub.

# Benchmark

libtssi2 is compared against the simple memory read operation `read`.

```c++
void read(span<const char> data) {
	for (auto v : data) {}
}
```

Only the time spent in libtssi2 or `read`is measured. Disc to memory transfers are omitted. Data is processed in 1MB chunks.

![libtssi benchmark](https://cldup.com/dTxpPi9lDf.thumb.png)

All tests were conducted on a HP Spectre x360 with Intel Core i7-7500U. The source code is available under [/examples/benchmark](./examples/benchmark).

# Quick start
We want to detect the transmission time of a Transport Stream. Let us suppose you already have included the stream and vector files from C++ and introduced the namespace `std` (a source file is available, see examples). 

First of all, we load a Transport Stream into a buffer variable.
```c++
	auto f = ifstream{ "examples/data/ard.ts", ifstream::binary };
	auto b = vector<char>( 4000000 );
	f.read(b.data(), b.size());
```
Keep in mind to check for errors in real programs. We skip this part to illustrate the API itself.

We now create a `TSParser` providing 188-byte TS packets and a `PSIHeap` that will process the packets and stores program-specific information.
```c++
	auto ts = tssi::TSParser<>();
	auto psi = tssi::PSIHeap<>();
```
The time and date information is stored on packets with PID `0x14`. We tell the parser what packets we are interested in and where to send them.
```c++
	ts.pid_parser({ 0x14 }, psi);
```
This COULD also be a lambda
```c++
	ts.pid_parser({ 0x100, 0x200, 0x300 }, [&] (auto data) { });
```
Or `PESAssembler` if you are interested in packetized elementary streams.

With the buffer and parser set up, we can process the data.
```c++
	ts(b);
```

The PSI table_ids we are looking for are `0x70` and `0x73`.
```c++
	for (auto& v : psi.psi_heap())
	    // v.first: section_identifier tuple 
	    //   (table_id, table_id_ext, section_number)
	    // v.second: PSISection
	    if ((get<0>(v.first) == 0x70) || (get<0>(v.first) == 0x73)) {
```
Direct access to the section's data is available through `v.second.psi_data()`.
```c++
            auto data = v.second.psi_data();
```
The functions to analyze sections and descriptors are organized in namespaces. Utilize the `using` statement if appropriate.
```c++
            using namespace tssi::etsi300468::time_date_section;
            auto time = UTC_time(data);
            cout << ctime(&time) << endl;
			break;
		}	
```
The program should result in an output like:
```sh
  Fri Oct 28 23:06:06 2005
```

# Examples

Advertise by utilize:

 - [Data](./examples/data/readme.md): 272MB Transport Stream sample (approx. 1min DVB satellite capture), test file for the following examples.
 - [Minimal](./examples/minimal/readme.md): The quick start guide's source code.
 - [Benchmark](./examples/benchmark/readme.md): Basic chronometry.
 - [PSI Data](./examples/psidata/readme.md): Parsing of Program-specific information to HTML.
 - [Audio/Video Parser](./examples/avparser/readme.md): Extraction of elementary stream (audio and video in this case) to disc.
 - [Multi-threading](./examples/multithreading/readme.md): A demo on reading from `PSIHeap` while `TSParser` tries to fill it with new information.
 - [Video player](./examples/videoplayer/readme.md): A video player using ffmpeg and SDL2.

# Building the docs

Should you want to build the docs for yourself, make [robodoc](http://rfsber.home.xs4all.nl/Robo/) available and use `doc.sh`or `doc.bat`. Modify the style either in the respective file or in `robodoc.rc`.




