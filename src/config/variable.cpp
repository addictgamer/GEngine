/* Please refer to license.txt */

#include "config.hpp"

#include "../string/string.hpp"

namespace GEngine
{

namespace mconfig
{

Variable::Variable()
{
	name = "";
}

Variable::~Variable()
{
}

bool Variable::isBool(const unsigned int x)
{
	if (x < values.size()) //Check if the value even exists.
	{
		if (mstring::stringToLower(values[x]) =="true" || mstring::stringToLower(values[x]) == "1")
		{
			return true; //It's true!
		}
		//Else it's either false or invalid input. Who cares? I do, but there ain't anything I can do about it!
	}

	return false; //Default case.
}

} //namespace mconfig

} //namespace GEngine
