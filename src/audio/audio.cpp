/* Please refer to license.txt */

#include <iostream>

#include "audio.hpp"

#include "../internal_header.hpp"

namespace GEngine
{

namespace maudio
{

//Basically an implementation specific thing. Wraps around whatever is being used. In this case, FMod.
class SoundData
{
public:
	//TODO: Write.
	SoundData()
	{
	}

	~SoundData()
	{
	}
};

Sound::Sound()
{
	data = nullptr;
}

Sound::~Sound()
{
}

bool Sound::load(std::string filepath)
{
	//TODO: Write.

	return true;
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

void AudioManager::play(Sound &sound)
{
	//TODO: Write.
}

} //namespace maudio

} //namespace GEngine
