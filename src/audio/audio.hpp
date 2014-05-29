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

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
}; //class AudioManager

} //namespace maudio

} //namespace GEngine
