/*-----------------------------------------------------------------------------

	ST-Sound ( YM files player library )

	This is a sample program: it's a real-time YM player using windows WaveOut API.

-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
* ST-Sound, ATARI-ST Music Emulator
* Copyright (c) 1995-1999 Arnaud Carre ( http://leonard.oxg.free.fr )
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*
-----------------------------------------------------------------------------*/

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#include "SoundServer.h"
#else
#include "SoundServerOpenAL.h"
#endif
#include "../StSoundLibrary/StSoundLibrary.h"


// Globals
static	volatile	YMMUSIC			*	s_pMusic = NULL;
static	CSoundServer					soundServer;

static	volatile	bool				ctrl_c = false;
static	void		termHandler(int)
{
	ctrl_c = true;
	signal(SIGINT, &termHandler);
}

static	void		soundServerCallback(void *pBuffer,long size)
{

	if (s_pMusic)
	{
		int nbSample = size / sizeof(ymsample);
		ymMusicCompute((void*)s_pMusic,(ymsample*)pBuffer,nbSample);
	}
}

enum endstate_t
{
	endstate_ok,
	endstate_abort,
	endstate_file,
	endstate_fatal
};

static	endstate_t	do_file(const char* pFileName, bool loop)
{

	endstate_t result = endstate_ok;

	printf("Loading music \"%s\"...\n",pFileName);
	YMMUSIC *pMusic = ymMusicCreate();
	s_pMusic = pMusic;			// global instance for soundserver callback

	if (ymMusicLoad(pMusic,pFileName))
	{
		if (soundServer.open(soundServerCallback,500))
		{

			ymMusicInfo_t info;
			ymMusicGetInfo(pMusic,&info);
			printf("Name.....: %s\n",info.pSongName);
			printf("Author...: %s\n",info.pSongAuthor);
			printf("Comment..: %s\n",info.pSongComment);
			printf("Duration.: %d:%02d\n",info.musicTimeInSec/60,info.musicTimeInSec%60);

			printf("\nPlaying music...(press Ctrl-C to abort)\n");

			signal(SIGINT, &termHandler);
			ymMusicSetLoopMode(pMusic,loop?YMTRUE:YMFALSE);
			ymMusicPlay(pMusic);

			int oldSec = -1;
			bool finished = false;
			while (!finished)
			{
				if (ctrl_c)
				{
					ctrl_c = false;
					break;
				}

				int sec = ymMusicGetPos(pMusic) / 1000;
				if (sec != oldSec)
				{
					// write to stderr, some platforms buffer stdout without \n
					fprintf(stderr,"Time: %d:%02d\r",sec/60,sec%60);
					oldSec = sec;
				}
				sleep(1);

				if (!loop && sec == info.musicTimeInSec) finished = true;
			}
			fprintf(stderr,"\n");

			// Switch off replayer
			s_pMusic = NULL;
			ymMusicStop(pMusic);
			soundServer.close();
			result = finished?endstate_ok:endstate_abort;
		}
		else
		{
			fprintf(stderr,"ERROR: Unable to initialize sound card hardware\n");
			result = endstate_fatal;
		}
	}
	else
	{
		fprintf(stderr,"Error in loading file %s:\n%s\n",pFileName,ymMusicGetLastError(pMusic));
		result = endstate_file;
	}

	ymMusicDestroy(pMusic);

	return result;
}

int main(int argc, char* argv[])
{

	//--------------------------------------------------------------------------
	// Checks args.
	//--------------------------------------------------------------------------
	printf(	"SmallYmPlayer.\n"
			"Using ST-Sound Library, under BSD license\n"
			"Copyright (C) 1995-1999 Arnaud Carre ( http://leonard.oxg.free.fr )\n");

	if (argc<2)
	{
		printf("Usage: SmallYmPlayer <ym music files>\n\n");
		return -1;
	}

	//--------------------------------------------------------------------------
	// Play YM music in a loop
	//--------------------------------------------------------------------------
	bool looping_a_single_file = (argc==2);
	do
	{
		for (int i = 1; i < argc; ++i)
		{
			switch (do_file(argv[i],looping_a_single_file))
			{
				case endstate_ok:
					break;
				case endstate_abort:
					sleep(1);
					if (ctrl_c) return 0;
					break;
				case endstate_fatal:
				case endstate_file:
					return -1;
			}
		}

	} while (!looping_a_single_file && !ctrl_c);

	return 0;
}
