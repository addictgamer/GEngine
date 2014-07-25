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
	//The sound's position.
	FMOD_VECTOR pos;

	FMOD::Sound* fmod_sound; //The FMOD sound data.

	SoundData();
	SoundData(float x, float y, float z);
	~SoundData();

	bool loadSound(std::string filepath, bool stream, bool loop);

	void setPos(float x, float y, float z);
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
	/*
	 * Note: To use the DSP:
result = channel->addDSP(dspecho, 0);
result = dspecho->setParameter(FMOD_DSP_ECHO_DELAY, 150.0f);
	 */
	FMOD::DSP* dsp_echo; //DSP for echo.

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
	//Track controls whether or not we want FMOD to keep tabs on the file (i.e. false = put it on whatever channel and just fire and forget)..
	void playSound(SoundData &sound, bool track);

	/*
	 * Plays the specified sound on the default channel so that it sounds like it's playing from the specified location.
	 * TODO: Multiple channels?
	 */
	//Track controls whether or not we want FMOD to keep tabs on the file (i.e. false = put it on whatever channel and just fire and forget)..
	void playSoundLoc(SoundData &sound, bool track, float x, float y, float z); //TODO: Implement this properly. All I did was copypasta so that GEngine compiles properly until I get around to actually implementing 3D sound.

	/*
	 * Plays the music (on the music channel).
	 */
	void playMusic(SoundData &music);

	void setVolume(FMOD::Channel &channel, float volume); //TODO: Expose this outside of the engine somehow. I guess I need to recreate channels now.
} extern *fmod_wrapper;

} //namespace maudio

} //namespace GEngine
