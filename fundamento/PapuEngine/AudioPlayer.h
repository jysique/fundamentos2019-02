#pragma once
#include <irrKlang/irrKlang.h>
#include <string>
#include <vector>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
using namespace irrklang;

class AudioPlayer
{
	ISoundEngine* audioPlayer;
	std::vector<ISoundSource*> sounds;
public:
	AudioPlayer();
	void addToTrack(const char* _musicPath);
	void playBackgroundSong();
	void playSong(int pos);
	~AudioPlayer();
};

