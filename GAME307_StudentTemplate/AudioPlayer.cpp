#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	audioList[0] = "assets/shot.wav";
	audioList[1] = "assets/hit.wav";
	audioList[2] = "assets/fire.wav";
	audioList[3] = "assets/engineIdle.wav";
	audioList[4] = "assets/engineStartup.wav";
	audioList[5] = "assets/hitDirt.wav";
	audioList[6] = "assets/flyby.wav";

	for (int i = 0; i < audioList.size(); ++i)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(audioList[i].c_str());
		audioChunks.push_back(chunk);
	}
}

AudioPlayer::~AudioPlayer()
{
	Mix_Quit();
}

void AudioPlayer::playAudio(int ID,int volume)
{
	if(!Mix_VolumeChunk(audioChunks[ID], volume));
	Mix_PlayChannel(ID, audioChunks[ID], 0);
}
