/* Please refer to license.txt */

#pragma once

#include "../graphic.hpp"

namespace GEngine
{

namespace mgfx
{

namespace d3d
{

class D3D
{
public:
	D3D();
	~D3D();

	//Sets up the 3D manager thingy.
	bool setup();

	//Updates the 3D manager thingy.
	void update();
};

} //namespace d3d

} //namespace mgfx

} //namespace GEngine
