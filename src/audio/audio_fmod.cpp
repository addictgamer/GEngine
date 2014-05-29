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

SoundData::~SoundData()
{
	//Free sound, if it's loaded.
	if (fmod_sound)
	{
		fmod_sound->release();
		fmod_sound = nullptr;
	}
}

bool SoundData::loadSound(std::string filepath)
{
	if (!fmod_wrapper)
	{
		std::cout << "\n[GEngine::maudio::SoundData::loadSound()] Error: FMOD needs to be intialized before a sound can be loaded.\n\n"; //TODO: Use GEngine errors.
		return false; //Need FMOD to be initialized before sound can be loaded.
	}

	FMOD_RESULT result;
	result = fmod_wrapper->fmod_system->createSound(filepath.c_str(), FMOD_LOOP_NORMAL, NULL, &fmod_sound); //Create the sound.
	if (fmod_wrapper->FMODErrorCheck(result))
	{
		std::cout << "\n[GEngine::maudio::SoundData::loadSound()] Error: Failed to load sound.\n\n"; //TODO: Use GEngine errors instead.
		return false; //Failed to load the sound.
	}

	return true;
}

FMODWrapper::FMODWrapper()
{
	fmod_system = nullptr;
	channel = nullptr;
	music_channel = nullptr;
}

FMODWrapper::~FMODWrapper()
{
	//Close system, if it's open.
	if (fmod_system)
	{
		fmod_system->release();
		fmod_system = nullptr;
	}
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

	return true;
}

bool FMODWrapper::FMODErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("\n[GEngine::maudio::FMOD error checker] FMOD error (%d \"%s\"\n\n", result, FMOD_ErrorString(result)); //TODO: GEngine errors instead.
		return true; //Error.
	}

	return false; //No error.
}

void FMODWrapper::update()
{
	if (!fmod_system)
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::update()] Warning: update called when FMOD system not initialized.\n\n"; //TODO: Use GEngine errors instead.
		return;
	}
	fmod_system->update();
}

void FMODWrapper::playSound(SoundData &sound)
{
	if (!sound.fmod_sound)
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::playSound()] Warning: Sound not loaded.\n\n"; //TODO: GEngine errors.
		return; //Sound not actually loaded.
	}

	FMOD_RESULT result;
	result = fmod_system->playSound(FMOD_CHANNEL_FREE, sound.fmod_sound, false, &channel); //TODO: Specify channel?
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
		std::cout << "\n[GEngine::maudio::FMODWrapper::playMusic()] Warning: Sound not loaded.\n\n"; //TODO: GEngine errors.
		return; //Sound not actually loaded.
	}

	FMOD_RESULT result;
	result = fmod_system->playSound(FMOD_CHANNEL_FREE, music.fmod_sound, false, &channel);
	if (FMODErrorCheck(result))
	{
		std::cout << "\n[GEngine::maudio::FMODWrapper::playMusic()] Error: Failed to play music.\n\n"; //TODO: GEngine errors.
		return; //Failed to open the channel or something.
	}
	fmod_system->update(); //Update the system.
}

Sound::Sound()
{
	data = nullptr;
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

bool Sound::load(std::string filepath)
{
	if (!data)
	{
		data = new SoundData(); //Allocate memory for the data.
	}

	if (!data->loadSound(filepath)) //Actually loads the sound.
	{
		return false;
	}

	return true;
}

void Sound::play()
{
	if (!fmod_wrapper)
	{
		std::cout << "\n[GEngine::maudio::AudioManager::playSound()] Warning: Attempted to play sound while FMOD was not initialized.\n\n"; //TODO: Gengine errors.
		return;
	}
	if (!data)
	{
		std::cout << "\n[GEngine::maudio::Sound::play()] Warning: Attempted to play sound while no data was loaded.\n\n"; //TODO: GEngine errors.
	}

	fmod_wrapper->playSound(*data);
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

void AudioManager::playSound(Sound &sound)
{
	if (!fmod_wrapper)
	{
		std::cout << "\n[GEngine::maudio::AudioManager::playSound()] Warning: Attempted to play sound while FMOD was not initialized.\n\n"; //TODO: Use GEngine errors instead.
		return;
	}

	sound.play();
}

void AudioManager::update()
{
	if (!fmod_wrapper)
	{
		std::cout << "\n[GEngine::maudio::AudioManager::update()] Warning: Updating while FMOD is not initialized.\n\n"; //TODO: Use GEngine errors instead.
		return; //Can't continue if FMOD is not initialized.
	}
	fmod_wrapper->update(); //Update FMOD.
}

} //namespace maudio

} //namespace GEngine
