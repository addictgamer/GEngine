/* Copyright Ciprian Ilies */

#pragma once

//At a proper point in time, remove the global_defines.hpp include and uncomment the internal_header.hpp include
#include "../internal_header.hpp" //Commenting out during development of the engine.

namespace mrand
{

void setup(); //Does setup stuff.

void seed(); //Seed it.

int randi(int min, int max); //Generates a random integer.

} //namespace mrand
