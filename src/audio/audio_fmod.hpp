/* Please refer to license.txt */

/*
 * This file contains all the defines for the FMOD implementation of the audio module.
 */

#pragma once

#include <string>
#include <vector>

#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>

#include "audio.hpp"

namespace GEngine
{

namespace maudio
{

#define FMOD_MAX_SOUNDS 32

/*
 * Basically an implementation specific thing. Wraps around whatever is being used. In this case, FMod.
 */
class SoundData
{
public:
	FMOD::Sound* fmod_sound; //The FMOD sound data.

	SoundData();
	~SoundData();

	bool loadSound(std::string filepath);
};

/*
 * Wraps around the FMOD library.
 */
class FMODWrapper
{
public:
	FMOD::System* fmod_system;
	FMOD::Channel* channel; //TODO: Multiple channels?
	FMOD::Channel* music_channel; //Music channels.

	FMODWrapper();

	~FMODWrapper();

	/*
	 * Initialize FMOD.
	 * Returns false on failure.
	 */
	bool initialize();

	/*
	 * Error handling function for FMOD.
	 * Returns:
	 *	true = FMOD error
	 *	false = no FMOD error
	 */
	bool FMODErrorCheck(FMOD_RESULT result);

	/*
	 * Updates FMOD.
	 */
	void update();

	/*
	 * Plays the specified sound on the default channel.
	 * TODO: Multiple channels?
	 */
	void playSound(SoundData &sound);

	/*
	 * Plays the music (on the music channel).
	 */
	void playMusic(SoundData &music);
} extern *fmod_wrapper;

} //namespace maudio

} //namespace GEngine
