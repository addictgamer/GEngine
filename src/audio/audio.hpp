/* Please refer to license.txt */

/*
 * This is the audio manager.
 * Its purpose is to manage all sounds and music.
 * TODO: Crossfading and stuff. Ya'know. Take the playing track, fade it out and then pause it, while at the same time taking the new track, and fading it in. Then optionally revert back to the first track again. So option to keep loaded track(s) permanent and whatnot.
 */

#pragma once

#include <string>
#include <vector>

//TODO: Sound groups & channels.

namespace GEngine
{

namespace maudio
{

class SoundData;

/*
 * A Sound is basically a loaded audio file.
 */
//TODO: 3D sounds. Not fully implemented yet. Only started on it. FINISH IT!
class Sound
{
private:
	SoundData *data; //Pointer to the sound's data.
	float x;
	float y;
	float z;
public:
	Sound();
	~Sound();

	/*
	 * Loads the sound from the specified file.
	 * Parameters:
	 *	filepath	=	the path to the audio file
	 *	loop:
	 *		true	=	the sound will loop
	 *		false	=	the sound won't loop
	 *	stream:
	 *		true	=	loads the sound as a stream (which means that when it doesn't load the audio file, it'll do that realtime)
	 *		false	=	will preload the entire sound file
	 */
	bool load(std::string filepath, bool loop = false, bool stream = false);

	/*
	 * Play the sound.
	 * Parameters:
	 *	soundeffect:
	 *		true = will play it as a sound efect. Just fire and forget. Doesn't even assign it a channel.
	 *		false = will assign the sound a channel and everything. Meant for music or other sounds that you want to keep tabs on.
	 */
	void play(bool soundeffect = false);

	/*
	 * Play a 3D sound.
	 */
	void playLoc(bool soundeffect, float x, float y, float z);
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
