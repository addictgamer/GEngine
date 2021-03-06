/* Please refer to license.txt */

#include <iostream>

#include <stdio.h>
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>

#include "../internal_header.hpp"

#include "audio.hpp"
#include "audio_fmod.hpp"

namespace GEngine
{

namespace maudio
{

FMODWrapper *fmod_wrapper;

SoundData::SoundData()
{
	fmod_sound = nullptr;
}

SoundData::SoundData(float x, float y, float z)
{
	fmod_sound = nullptr;
	pos = {x, y, z};
}

SoundData::~SoundData()
{
	//Free sound, if it's loaded.
	if (fmod_sound)
	{
		fmod_sound->release();
		fmod_sound = nullptr;
	}
}

bool SoundData::loadSound(std::string filepath, bool stream, bool loop)
{
	if (!fmod_wrapper)
	{
		std::cout << "\n[GEngine::maudio::SoundData::loadSound()] Error: FMOD needs to be intialized before a sound can be loaded.\n\n"; //TODO: Use GEngine errors.
		return false; //Need FMOD to be initialized before sound can be loaded.
	}

	FMOD_RESULT result;
	FMOD_MODE mode = FMOD_SOFTWARE; //The sound's mode. By default, we're going to use software mixing.
	if (loop)
	{
		mode |= FMOD_LOOP_NORMAL; //Loop it.
	}
	if (stream)
	{
		result = fmod_wrapper->fmod_system->createStream(filepath.c_str(), mode, NULL, &fmod_sound); //Create the sound as a stream.
	}
	else
	{
		result = fmod_wrapper->fmod_system->createSound(filepath.c_str(), mode, NULL, &fmod_sound); //Create the sound.
	}
	if (fmod_wrapper->FMODErrorCheck(result))
	{
		std::cout << "\n[GEngine::maudio::SoundData::loadSound()] Error: Failed to load sound.\n\n"; //TODO: Use GEngine errors instead.
		return false; //Failed to load the sound.
	}

	return true;
}

void SoundData::setPos(float x, float y, float z)
{
	pos = {x, y, z};
}

FMODWrapper::FMODWrapper()
{
	fmod_system = nullptr;
	channel = nullptr;
	music_channel = nullptr;
	dsp_echo = nullptr;
}

FMODWrapper::~FMODWrapper()
{
	//Close system, if it's open.
	if (fmod_system)
	{
		fmod_system->close();
		fmod_system->release();
		fmod_system = nullptr;
	}

	//TODO: Close channels?
	//TODO: Close DPSs?
}

bool FMODWrapper::initialize()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&fmod_system);
	if (FMODErrorCheck(result))
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::initialize()] Error: Failed to create FMOD system.\n\n"; //TODO: Use GEngine errors instead.
		return false; //Failed to allocate memory for FMOD and such. Not sure what System_Create entails besides memory allocation.
	}

	fmod_system->setOutput(FMOD_OUTPUTTYPE_DSOUND);
	result = fmod_system->init(FMOD_MAX_SOUNDS, FMOD_INIT_NORMAL, 0); //TODO: Initialize FMOD how we need/want it.
	if (FMODErrorCheck(result))
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::initialize()] Error: Failed to initialize FMOD system.\n\n"; //TODO: Use GEngine errors instead.
		return false; //Failed to initialize FMOD.
	}

	result = fmod_system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp_echo);
	if (FMODErrorCheck(result))
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::initialize()] Error: Failed to create echo DSP.\n\n"; //TODO: Use GEngine errors instead.
		return false; //Failed to create echo DSP.
	}

	return true;
}

bool FMODWrapper::FMODErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("\n[GEngine::maudio::FMOD error checker] FMOD error (%d): \"%s\"\n\n", result, FMOD_ErrorString(result)); //TODO: GEngine errors instead.
		return true; //Error.
	}

	return false; //No error.
}

void FMODWrapper::update()
{
	if (!fmod_system)
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::update()] Error: update called when FMOD system not initialized.\n\n"; //TODO: Use GEngine errors instead.
		return;
	}
	fmod_system->update();
}

void FMODWrapper::playSound(SoundData &sound, bool track)
{
	if (!sound.fmod_sound)
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::playSound()] Error: Sound not loaded.\n\n"; //TODO: GEngine errors.
		return; //Sound not actually loaded.
	}

	FMOD_RESULT result;
	result = fmod_system->playSound(FMOD_CHANNEL_FREE, sound.fmod_sound, false, (track) ? &channel : nullptr); //TODO: Specify channel?
	
	if (FMODErrorCheck(result))
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::playSound()] Error: Failed to play sound.\n\n"; //TODO: GEngine errors.
		return; //Failed to open the channel or something.
	}
	fmod_system->update(); //Update the system.
}

void FMODWrapper::playSoundLoc(SoundData &sound, bool track, float x, float y, float z) //TODO: Implement this properly. All I did was copypasta so that GEngine compiles properly until I get around to actually implementing 3D sound.
{
	if (!sound.fmod_sound)
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::playSound()] Error: Sound not loaded.\n\n"; //TODO: GEngine errors.
		return; //Sound not actually loaded.
	}

	FMOD_RESULT result;
	result = fmod_system->playSound(FMOD_CHANNEL_FREE, sound.fmod_sound, false, (track) ? &channel : nullptr); //TODO: Specify channel?
	
	if (FMODErrorCheck(result))
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::playSound()] Error: Failed to play sound.\n\n"; //TODO: GEngine errors.
		return; //Failed to open the channel or something.
	}
	fmod_system->update(); //Update the system.
}

void FMODWrapper::playMusic(SoundData &music)
{
	if (!music.fmod_sound)
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::playMusic()] Error: Sound not loaded.\n\n"; //TODO: GEngine errors.
		return; //Sound not actually loaded.
	}

	FMOD_RESULT result;
	result = fmod_system->playSound(FMOD_CHANNEL_FREE, music.fmod_sound, false, &music_channel);
	if (FMODErrorCheck(result))
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::playMusic()] Error: Failed to play music.\n\n"; //TODO: GEngine errors.
		return; //Failed to open the channel or something.
	}
	fmod_system->update(); //Update the system.
}

void FMODWrapper::setVolume(FMOD::Channel &channel, float volume)
{
	channel.setVolume(volume);
}

Sound::Sound()
{
	data = nullptr;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Sound::~Sound()
{
	//TODO: Free sound, if it's loaded.
	if (data)
	{
		//Free the data;
		delete data;
		data = nullptr;
	}
}

bool Sound::load(std::string filepath, bool loop, bool stream)
{
	if (!data)
	{
		data = new SoundData(); //Allocate memory for the data.
	}

	if (!data->loadSound(filepath, stream, loop)) //Actually loads the sound.
	{
		std::cout << "\n[GEngine::maudio::Sound::load()] Error: Failed to load sound \"" << filepath << "\".\n\n"; //TODO: Use GEngine errors instead.
		return false;
	}

	return true;
}

void Sound::play(bool soundeffect)
{
	if (!fmod_wrapper)
	{
		std::cout << "\n[GEngine::maudio::Sound::playSound()] Error: Attempted to play sound while FMOD was not initialized.\n\n"; //TODO: Gengine errors.
		return;
	}
	if (!data)
	{
		std::cout << "\n[GEngine::maudio::Sound::play()] Error: Attempted to play sound while no data was loaded.\n\n"; //TODO: GEngine errors.
		return;
	}

	fmod_wrapper->playSound(*data, soundeffect);
}

void Sound::playLoc(bool soundeffect, float x, float y, float z)
{
	if (!fmod_wrapper)
	{
		std::cerr << "\b[GEngine::maudio::Sound::playLoc()] Error: Attempted to play sound while FMOD was not initialized.\n\n"; //TODO: Gengine errors.
		return;
	}
	if (!data)
	{
		std::cout << "\n[GEngine::maudio::Sound::playLoc()] Error: Attempted to play sound while no data was loaded.";
		return;
	}

	fmod_wrapper->playSoundLoc(*data, soundeffect, x, y, z);
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

bool AudioManager::initialize()
{
	if (!fmod_wrapper)
	{
		//Allocate memory for the FMOD wrapper.
		fmod_wrapper = new FMODWrapper();
		//Initialize the fmod wrapper.
		if (!fmod_wrapper->initialize())
		{
			return false; //Failed to initialize the FMOD wrapper.
		}
	}

	return true;
}

/*void AudioManager::playSound(Sound &sound)
{
	if (!fmod_wrapper)
	{
		std::cout << "\n[GEngine::maudio::AudioManager::playSound()] Warning: Attempted to play sound while FMOD was not initialized.\n\n"; //TODO: Use GEngine errors instead.
		return;
	}

	sound.play();
}*/

void AudioManager::update()
{
	if (!fmod_wrapper)
	{
		std::cout << "\n[GEngine::maudio::AudioManager::update()] Error: Updating while FMOD is not initialized.\n\n"; //TODO: Use GEngine errors instead.
		return; //Can't continue if FMOD is not initialized.
	}
	fmod_wrapper->update(); //Update FMOD.
}

void AudioManager::playMusic(Sound &music)
{
	if (!fmod_wrapper)
	{
		std::cout << "\n[GEngine::maudio::AudioManager::playMusic()] Error: Attempted to play music while FMOD was not initialized.\n\n"; //TODO: Use GEngine errors instead.
		return;
	}

	music.play(false);
}

} //namespace maudio

} //namespace GEngine
