/* Please refer to license.txt */

/*
 * Time stuff.
 */

//Purpose: injectTimePulse( float timeElapsed ); into CEGUI (both the GUI context and the system context). ( http://www.cegui.org.uk/api_reference/input_tutorial.html )

#pragma once

#include <SFML/System.hpp>

#include "../string/string.hpp"
#include "../error/error.hpp"

namespace GEngine
{

namespace mmisc
{

namespace mtime
{

//So, just run one of these in the interface module and use it to injectTimePulse into what CEGUI wants.
class Timer
{
private:
	sf::Clock *clock; //The internal sfml clock running things.
public:
	Timer()
	{
		clock = nullptr;
	}
	~Timer()
	{
		if (clock)
		{
			delete clock;
			clock = nullptr;
		}
	}

	/*
	 * Starts the timer.
	 */
	void start()
	{
		if (clock) //Clock already exists. That means the timer has already been initiated. What is this fool doing???
		{
			delete clock; //Oh well, let's delete it for now and then create it anew.
		}

		clock = new sf::Clock(); //Create the clock (that is, allocate memory for it).
	}

	/*
	 * Returns the time elapsed.
	 * TODO: Wrap around SFML's "get time in any format (eg seconds, milleseconds, microseconds, etc" feature.
	 */
	int timeElapsed()
	{
		if (!clock)
		{
			//Error. IN THEIR FACE. What dolt calls a timer without initiating it first? They should check their code. (I wouldn't be surprised if I forgot to initialize a timer before using it -- I know, I've done things like this before.
			std::string *filename = new std::string; //The filename.
			*filename = mstring::toString(__FILE__); //Convert the char* that is filename to a string.
			std::string *message = new std::string;
			*message = "[mmisc::mtime::Timer::timeElapsed()] Error...IN YOUR FACE! The programmer forgot to initialize the timer first!";
			merror::Error *error = generateError(merror::FUNCTION_FAILURE, message, merror::SEVERITY_IGNORE, __LINE__, filename);
			throw error;
		}

		return clock->restart().asMilliseconds();
	}

	/*
	 * SFML's clock doesn't have a stop function. What should I do about that? It's not really necessary, I guess.
	 */
};

} //namespace mtime

} //namespace mmisc

} //namespace GEngine
