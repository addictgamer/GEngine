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
	cegui_renderer = nullptr;
	cegui_gui_context = nullptr;
	default_d2d = false;
}

D2D::~D2D()
{
	window = nullptr;

	if (!default_d2d) //Don't delete them if default because the default GUI context is CEGUI's responsibility.
	{
		if (cegui_renderer)
		{
			//delete cegui_renderer;
			CEGUI::OpenGLRenderer::destroy(*cegui_renderer);
			cegui_renderer = nullptr;
		}

		if (cegui_gui_context)
		{
			CEGUI::System::getSingleton().destroyGUIContext(*cegui_gui_context);
			cegui_gui_context = nullptr;
		}
	}
}

bool D2D::setup()
{
	return true; //Success.
}

void D2D::setWindow(Window &_window)
{
	window = &_window;
}

void D2D::update()
{
}

CEGUI::Window* D2D::getRootWindow()
{
	return cegui_root_window;
}

void D2D::setRootWindow(CEGUI::Window *window)
{
	cegui_root_window = window;
	cegui_gui_context->setRootWindow(cegui_root_window);
}

} //namespace d2d

} //namespace mgfx

} //namespace GEngine
