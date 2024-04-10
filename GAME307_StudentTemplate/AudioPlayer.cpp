#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) printf("Failed to init SDL_Sound");
	if (!Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) printf("Failed to open SDL_Audio");

	audioList[0] = "assets/shot.wav";
	audioList[1] = "assets/hit.wav";
	audioList[2] = "assets/fire.wav";
	audioList[3] = "assets/engineIdle.wav";
	audioList[4] = "assets/engineStartup.wav";

	for (int i = 0; i < audioList.size(); ++i)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(audioList[i].c_str());
		audioChunks.push_back(chunk);
	}
}

AudioPlayer::~AudioPlayer()
{
	for (auto c : audioChunks)
	{
		Mix_FreeChunk(c);
	}
	Mix_Quit();
}

void AudioPlayer::playAudio(int ID)
{
	Mix_PlayChannel(-1, audioChunks[ID], 0);
}
