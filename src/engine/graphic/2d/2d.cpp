/* Copyright Ciprian Ilies */

#include "2d.hpp"

#include "../window/window.hpp"

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

bool D2D::setWindow(Window &_window)
{
	window = &_window;
	return true; //Success.
}

} //namespace d2d

} //namespace mgfx
