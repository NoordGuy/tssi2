# A simple video player based on ffmpeg + SDL2 + libtssi

This examples uses the PESAssembler to generate elementary streams (ES). By decoding them with ffmpeg and rendering the output with SDL2, a simple video player is written.

Additional dependencies:

  - [ffmpeg](https://www.ffmpeg.org/) (v3.3+), libraries: avcodec, avutil, swscale 
  - [SDL2](https://www.libsdl.org/) (v2.0.5+), libraries: SDL2, SDL2main
