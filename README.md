# StSound
Library to replay YM files ( Atari ST music file format )

written by Arnaud Carré (aka Leonard/Oxygene)

[@leonard_coder](https://twitter.com/leonard_coder)


# History
In 1995 I created the YM file format and wrote ST-Sound, a program to play ATARI-ST on your PC. I was very happy to see how ST-Sound was popular. MS-Dos player at first, I wrote a Windows player, a winamp and a netscape plugin. ( then some website use Atari tunes !).
And then time passed and I worked on other stuff. Quite often, some people asked me to release the source code, and I always answered that I should clean some code and add license stuff, so I never take time..
Now it's done ! 2005, ten years after the first ST-Sound creation, here is the ST-Sound library with sample project, all under BSD license. The code is not as clean as I hope but no time to change it. Don't forget almost all that stuff was written in 1995 :-)

2020 update: I just created this github repo, easier to use than a zip file on my website :)

# Repository details
ST-Sound library repo comes with four main directories.:

1. **StSoundLibrary**
This is the most important directory. Portable ( I hope !! :-)) C++ code to play YM files into your own production. There is a simple "C like" user API, and you just need to include "StSoundLibrary.h" to work with YM files. See tutorial projects for details. Theorically should compile under windows, linux, etc.

2. **YmToWav**
Tutorial code. Portable ( I hope !! :-)) code to render an YM file into a WAV file. Works in command line. theorically should compile under windows, linux, etc.

3. **SmallYmPlayer**
Tutorial code. Non portable (windows only) real time YM player using StSoundLibrary. Works under windows (use the waveOut sound API)

4. **YmSampleFiles**
Only contains a set of YM sample files to fastly test the library without browsing the whole world wide web ! :-)

# Compiling
The package is done to work very nicely with Microsoft Visual Studio

For Visual Studio users: Load StSound_vc2017.sln file into your lovely IDE and just build one of the tutorial sample or the main library. Everything should work without pain
For other users ( Linux, Gameboy color or any strange system), just search in your head some very, very oldschool knowledge and build a nice makefile :-) ( should be easy for StSoundLibrary)

## Compile on MacOS (and presumably Linux)

```bash
mkdir build
cd build
cmake ..
make
```

This will compile SmallYmPlayer, StSoundLibrary and (most importantly) Ym2Wav, the latter of which can be used
on the shell to convert YM files to WAV like this:

```
# from the build directory
./Ym2Wav/Ym2Wav ../YmSampleFiles/ANCOOL1.YM ancool1.wav

# to play ancool1.wav run
play ancool1.wav
# or
aplay ancool1.wav
```

SmallYmPlayer has been patched such that it compiles on non-Windows system, but if you run it, it will only tell you that it can't run :)


# Legal
ST-Sound library is written by Arnaud Carré and is public domain. You can use it as you wish. If you're using it in your project, any credits in any readme file is appreciated :)
As almost all YM files on the web are packed with LZH method, ST-Sound includes LZH depacking code written by Haruhiko Okumura and modifyed/improved by Kerwin F. Medina.

# Enjoy!




