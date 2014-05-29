/* Please refer to license.txt */

/*
 * This is the audio manager.
 * Its purpose is to manage all sounds and music.
 * TODO: Crossfading and stuff. Ya'know. Take the playing track, fade it out and then pause it, while at the same time taking the new track, and fading it in. Then optionally revert back to the first track again. So option to keep loaded track(s) permanent and whatnot.
 */

#pragma once

#include <string>
#include <vector>

namespace GEngine
{

namespace maudio
{

class SoundData;

/*
 * A Sound is basically a loaded audio file.
 */
class Sound
{
private:
	//TODO: Data and such here.
	SoundData *data; //Pointer to the sound's data. //TODO: Write.
public:
	Sound();
	~Sound();

	/*
	 * Loads the sound from the specified file.
	 */
	bool load(std::string filepath); //TODO: Write.
};

//TODO: List of playing sounds?
class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	/*
	 * Plays the specified sound.
	 */
	void play(Sound &sound); //TODO: Write.
}; //class AudioManager

} //namespace maudio

} //namespace GEngine
