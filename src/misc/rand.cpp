/* Please refer to license.txt */

#include "rand.hpp"

#include <time.h>
#include <cstdlib>

namespace mrand
{

void setup()
{

	seed(); //Seed itself.

}

void seed()
{
	 srand(time(NULL)); //Give it a random seed based on time.
}

int randi(int min, int max)
{
	return rand() % max + min; //Return the random number.
}

} //namespace mrand
