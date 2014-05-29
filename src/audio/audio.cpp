/* Please refer to license.txt */

#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "audio.hpp"

#include "../error/error.hpp"

#include "../string/string.hpp"

#include "../internal_header.hpp"

namespace GEngine
{

namespace maudio
{

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

} //namespace maudio

} //namespace GEngine
