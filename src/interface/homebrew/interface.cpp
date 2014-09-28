/* Please refer to license.txt */

#include "interface.hpp"

#include <iostream>

#include "../../graphic/2d/2d.hpp"
#include "../../graphic/window/window.hpp"

#include "../../misc/time.hpp"

#include "../../file/file.hpp"

#include "../interface.hpp"

namespace GEngine
{

namespace mui
{

namespace homebrew
{

Button::Button()
{
	x = 0;
	y = 0;
}

Button::~Button()
{
}

void Button::initialize(int arg_x, int arg_y, mgfx::d2d::D2D &arg_d2d) //TODO: Sprite.
{
	x = arg_x;
	y = arg_y;
	d2d = &arg_d2d;
}

bool Button::checkLeftClicked()
{
	if (!d2d)
	{
		std::cout << "[GEngine::mui::homebrew::Button::checkLeftClicked()] ERROR: D2D does not exist. Aborting check. Please resolve.\n"; //TODO: Proper error?
		return false; //ERROR.
	}
	if (d2d->window)
	{
		//TODO: Make it work (looks like D2Ds will have to keep track of their interfaces)
		/*std::vector<unhandledEvent>::iterator iter = interface->unhandled_events.begin();
		for (; iter != interface->unhandled_events.end(); ++iter) //Loop through all the events.
		{
			sf::Event &event = (*iter).event;
			mgfx::Window &window = (*iter).window;
			switch (event.type)
			{
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left) {
						//Do something? Used to click a space. But that's not currently implemented...
					}
					break;
				default:
					break;
			}
		}*/
	}
	return false;
}

} //namespace homebrew

} //namespace mui

} //namespace GEngine
