/* Copyright Ciprian Ilies */

#pragma once

//At a proper point in time, remove the global_defines.hpp include and uncomment the internal_header.hpp include
#include "../internal_header.hpp" //Commenting out during development of the engine.

#include <stdio.h>
#include <stdlib.h>

namespace mmath
{

#define PI 3.14159265

#define degrees_to_radians (PI / 180)

//Manages an angle (such as wrapping it around when it goes under/over the specified min/max.)
//The second and third parameters have been explained above, as for angle, that is obvious.
//It's the input angle.
//The result is returned.
float manageAngle(float angle, float max, float min);


} //namespace mmath
