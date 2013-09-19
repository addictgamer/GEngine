/* Please refer to license.txt */

#pragma once

#include "../graphic.hpp"

namespace GEngine
{

namespace mgfx
{

class Window; //Forward declaration.

namespace d3d
{

class D3D
{
public:
	Window *window; //The window being used with this. //NOTE: Please do NOT change this at runtime. Create a new d2d for every window.

	D3D();
	~D3D();

	//Sets up the 3D manager thingy.
	bool setup();

	//Be sure to call setWindow() before using D3D!
	void setWindow(Window &_window);

	//Updates the 3D manager thingy.
	void update();
};

} //namespace d3d

} //namespace mgfx

} //namespace GEngine
