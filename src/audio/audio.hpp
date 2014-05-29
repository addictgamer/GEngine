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
//TODO: 3D sounds.
class Sound
{
private:
	SoundData *data; //Pointer to the sound's data.
public:
	Sound();
	~Sound();

	/*
	 * Loads the sound from the specified file.
	 */
	bool load(std::string filepath);

	/*
	 * Play the sound.
	 */
	void play();
};

//TODO: List of playing sounds?
//TODO: Multiple devices?
class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	/*
	 * Initializes the audio system.
	 * Returns false on failure.
	 */
	bool initialize();

	/*
	 * Plays the specified sound.
	 */
	//void playSound(Sound &sound); //Call the sound's play function instead.

	/*
	 * Updates whatever needs updating with the audio.
	 */
	void update();

	/*
	 * Set the music.
	 * //TODO: fade transition and stuff.
	 */
	void playMusic(Sound &music);
}; //class AudioManager

} //namespace maudio

} //namespace GEngine
