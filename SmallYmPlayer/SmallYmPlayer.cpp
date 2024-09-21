#ifdef _WIN32

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

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "SoundServer.h"
#include "../StSoundLibrary/StSoundLibrary.h"


// Globals
static	volatile	YMMUSIC			*	s_pMusic = NULL;
static	CSoundServer					soundServer;



static	void	soundServerCallback(void *pBuffer,long size)
{

	if (s_pMusic)
	{
		int nbSample = size / sizeof(ymsample);
		ymMusicCompute((void*)s_pMusic,(ymsample*)pBuffer,nbSample);
	}
}





int main(int argc, char* argv[])
{

	//--------------------------------------------------------------------------
	// Checks args.
	//--------------------------------------------------------------------------
	printf(	"SmallYmPlayer.\n"
			"Using ST-Sound Library, under BSD license\n"
			"Copyright (C) 1995-1999 Arnaud Carre ( http://leonard.oxg.free.fr )\n");
	
	if (argc!=2)
	{
		printf("Usage: SmallYmPlayer <ym music file>\n\n");
		return -1;
	}


	//--------------------------------------------------------------------------
	// Load YM music and creates WAV file
	//--------------------------------------------------------------------------
	printf("Loading music \"%s\"...\n",argv[1]);
	YMMUSIC *pMusic = ymMusicCreate();

	if (ymMusicLoad(pMusic,argv[1]))
	{
		if (soundServer.open(soundServerCallback,500))
		{

			ymMusicInfo_t info;
			ymMusicGetInfo(pMusic,&info);
			printf("Name.....: %s\n",info.pSongName);
			printf("Author...: %s\n",info.pSongAuthor);
			printf("Comment..: %s\n",info.pSongComment);
			printf("Duration.: %d:%02d\n",info.musicTimeInSec/60,info.musicTimeInSec%60);
			printf("Driver...: %s\n", info.pSongPlayer);

			printf("\nPlaying music...(press a key to abort)\n");

			ymMusicSetLoopMode(pMusic,YMTRUE);
			ymMusicPlay(pMusic);
			s_pMusic = pMusic;			// global instance for soundserver callback

			int oldSec = -1;
			for (;;)
			{
				if (_kbhit())
					break;

				int sec = ymMusicGetPos(pMusic) / 1000;
				if (sec != oldSec)
				{
					printf("Time: %d:%02d\r",sec/60,sec%60);
					oldSec = sec;
				}

				Sleep(20);
			}
			_getch();		// flush the key pressed
			printf("\n");

			// Switch off replayer
			s_pMusic = NULL;
			ymMusicStop(pMusic);
			soundServer.close();

		}
		else
		{
			printf("ERROR: Unable to initialize sound card hardware\n");
		}

	}
	else
	{
		printf("Error in loading file %s:\n%s\n",argv[1],ymMusicGetLastError(pMusic));
	}

	ymMusicDestroy(pMusic);

	return 0;
}
#else

#include <stdio.h>

int main(int argc, char* argv[])
{
	printf(	"SmallYmPlayer only run on Windows, sorry!\n");
	return 0;	
}

#endif
