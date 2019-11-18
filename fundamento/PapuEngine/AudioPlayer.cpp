#include "AudioPlayer.h"


AudioPlayer::AudioPlayer()
{
	audioPlayer = createIrrKlangDevice();
}

void AudioPlayer::addToTrack(const char* _musicPath)
{
	ISoundSource* newSound = audioPlayer->addSoundSourceFromFile(_musicPath);
	sounds.push_back(newSound);
}

void AudioPlayer::playBackgroundSong()
{
	audioPlayer->play2D(sounds[0], true);
}

void AudioPlayer::playSong(int pos)
{
	audioPlayer->play2D(sounds[pos]);
}

AudioPlayer::~AudioPlayer()
{
	audioPlayer->drop();
}
