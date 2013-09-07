/* Please refer to license.txt */

#include "math.hpp"
#include <math.h>

namespace mmath
{

float manageAngle(float angle, float max, float min)
{
	float result = angle; //The result.

	while (result > max) //Overflow. Resolve.
	{
		float overflow = result - max;
		result = overflow; //Reset it to the overflow.

		//This loop will keep subtracting max from angle until its in an acceptable range.
	}
	while (result < min) //Underflow. Resolve it.
	{
		float underflow = min - fabs(result); //Get the underflow value.
		result = 360 - fabs(underflow); //Reset it using the absolute value of the underflow.

		//Same as above.
	}

	return result;
}

} //namespace mmath
