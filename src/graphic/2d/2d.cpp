/* Please refer to license.txt */

#include "2d.hpp"

#include "../window/window.hpp"

namespace GEngine
{

namespace mgfx
{

namespace d2d
{

D2D::D2D()
{
	window = nullptr;
}

D2D::~D2D()
{
	window = nullptr;
}

bool D2D::setup()
{
	return true; //Success.
}

void D2D::update()
{
}

void D2D::setWindow(Window &_window)
{
	window = &_window;
}

} //namespace d2d

} //namespace mgfx

} //namespace GEngine
