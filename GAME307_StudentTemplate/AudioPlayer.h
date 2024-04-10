#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <unordered_map>
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>

class AudioPlayer
{
	std::unordered_map<int, std::string> audioList;
	std::vector<Mix_Chunk*> audioChunks;
public:
	AudioPlayer();
	~AudioPlayer();

	void playAudio(int ID);
};
#endif
