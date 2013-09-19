/* Please refer to license.txt */

#include "3d.hpp"

#include "../window/window.hpp"

namespace GEngine
{

namespace mgfx
{

namespace d3d
{

D3D::D3D()
{
	window = nullptr;
}

D3D::~D3D()
{
	window = nullptr;
}

bool D3D::setup()
{
	return true; //Success.
}

void D3D::setWindow(Window &_window)
{
	window = &_window;
}

void D3D::update()
{
}

} //namespace d3d

} //namespace mgfx

} //namespace GEngine
