/* Please refer to license.txt */

#include "window.hpp"

#include "../2d/2d.hpp"

#include <iostream>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>

namespace GEngine
{

namespace mgfx
{

Window::Window()
{
	parent_d2d = nullptr;

	width = nullptr;
	height = nullptr;
	delete_width = false;
	delete_height = false;

	fullscreen = false;

	windowname = "";

	window2d = nullptr;
	event = nullptr;

	closed = true;
	can_close = true;

	focus = true;
}

Window::~Window()
{
	if (width) //If the width exists.
	{
		if (delete_width) //If it should be deleted.
		{
			delete width; //Delete it.
			width = nullptr; //Reset it.
		}
		else
		{
			width = nullptr; //Don't delete it, simply reset it.
		}
	}

	if (height) //If the height exists.
	{
		if (delete_height) //Delete it.
		{
			delete height; //Delete it.
			height = nullptr; //Reset it.
		}
		else
		{
			height = nullptr; //Don't delete it, only reset it.
		}
	}

	if (window2d) //If the 2d window exists.
	{
		window2d->close(); //Close the window.
		delete window2d; //Delete the window.
		window2d = nullptr; //Reset it.
	}

	if (event) //If the event exists.
	{
		delete event; //Delete it.
		event = nullptr; //Set to null.
	}
}

bool Window::create(int _width, int _height, bool _fullscreen, std::string _windowname, bool use_opengl)
{
	if (width) //Delete the width if it exists.
	{
		delete width;
	}
	width = new int; //Allocate memory for the width.
	delete_width = true; //The width is to be deleted.
	*width = _width; //Store the width.

	if (height) //Delete the height if it exists.
	{
		delete height;
	}
	height = new int; //Allocate memory for the height.
	delete_height = true; //The height is to be deleted.
	*height = _height; //Store the height.

	fullscreen = _fullscreen; //Store the fullscreen state.

	windowname = _windowname; //Store the window name.

	//TODO: Point the width and the height to the SFML window's width and height? Don't know if that's possible.
	window2d = new sf::RenderWindow; //Create a new (2d) window.

	if(fullscreen) //If it is to be fullscreen, do it.
	{
		window2d->create(sf::VideoMode(*width, *height), _windowname, sf::Style::Fullscreen); //Make the window fullscreen.
	}
	else
	{
		window2d->create(sf::VideoMode(*width, *height), _windowname, sf::Style::Default); //Nope, just a normal window.
	}

	closed = false; //Not closed.

	if (event) //If it already exists.
	{
		delete event; //Delete it.
	}
	event = new sf::Event; //Allocate memory for it.

	//TODO: Error checking?

	return true; //Success.
}

void Window::update()
{
	events.clear(); //Reset all events.

	if (!closed && window2d && event) //If the window is open, the window exists, and event exists.
	{
		while (window2d->pollEvent(*event)) //Poll events. //TODO: Give access to these events to the game.
		{
			if (event->type == sf::Event::Closed && can_close) //Check if the event is a window close.
			{
				window2d->close(); //Close the window.
				closed = true; //Update that it's closed.
			}
			else if (event->type == sf::Event::Resized && !closed && window2d) //Window resized. //TODO: Make a can_resize check.
			{
				window2d->setView(sf::View(sf::FloatRect(0, 0, event->size.width, event->size.height)));
				//CEGUI::Sizef size(event->size.width, event->size.height);
				//CEGUI::System::getSingleton().notifyDisplaySizeChanged(size); //Notify CEGUI of the changed size.
				//CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(event->size.width, event->size.height)); //Notify CEGUI of the changed size. //TODO: Notify the GUI context involved.
				if (parent_d2d && parent_d2d->cegui_renderer)
				{
					parent_d2d->cegui_renderer->setDisplaySize(CEGUI::Size<float>(event->size.width, event->size.height));
				}
			}
			else if (event->type == sf::Event::LostFocus)
			{
				focus = false; //Lost focus.
			}
			else if (event->type == sf::Event::GainedFocus)
			{
				focus = true; //Gained focus.
			}
			else
			{
				if (event->type == sf::Event::MouseButtonPressed)
				{
					if (event->mouseButton.button == sf::Mouse::Left)
					{
						std::cout << "[WINDOW] the left button was pressed" << std::endl;
					}
				}
				events.push_back(*event); //Save the event for later processing.
			}
		}
	}
}
void Window::draw()
{
	if (!closed && window2d) //If the window was not closed.
	{
		window2d->display(); //Display the window.
		window2d->clear();
	}
}

int Window::getWidth()
{
	if (!window2d)
	{
		std::cout << "\nNo 2d window, fool.\n";
		return -1;
	}

	if (!width || !delete_width) //If width does not exist or if it should not be deleted (meaning it's pointing to some other int).
	{
		width = new int; //Allocate it.
		delete_width = true; //It will be deleted.
	}

	sf::Vector2u vector = window2d->getSize(); //Get the size.

	*width = vector.x; //Set/update the width.

	return *width; //Return the width.
}

int Window::getHeight()
{
	if (!window2d)
	{
		std::cout << "\nNo, seriously, there is no 2d window! Why don't you understand?\n";
		return -1;
	}

	if (!height || !delete_height) //If height does not exist or if it should not be deleted (meaning it's pointing to some other int).
	{
		height = new int; //Allocate it.
		delete_height = true; //It will be deleted.
	}

	sf::Vector2u vector = window2d->getSize(); //Get the size of the window.

	*height = vector.y; //Set/update the height.

	return *height; //Return the height.
}

int Window::getX()
{
	return window2d->getPosition().x;
	//return (using_opengl) ? /*3d*/window3d->getPosition().x /*window*/ : /*2d*/ window2d->getPosition().x /*window*/;
}

int Window::getY()
{
	return window2d->getPosition().y;
	//return (using_opengl) ? /*3d*/window3d->getPosition().y /*window*/ : /*2d*/ window2d->getPosition().y /*window*/;
}

void Window::drawSprite(mgfx::d2d::Sprite &sprite)
{
	if (!window2d)
	{
		std::cout << "\nAnd just what are you trying to achieve with a window that does not exist?\n";
		return;
	}

	window2d->draw(*sprite.sprite); //Draw the sprite.
}

void Window::renderText(std::string text, int _x, int _y, int font_size, sf::Font &font)
{
	sf::Text _text(text, font);
	_text.setCharacterSize(font_size);
	_text.setPosition(_x, _y);

	if (!window2d)
	{
		std::cout << "\nAnd just what are you trying to achieve with a 2D window that does not exist?\n";
		return;
	}
	window2d->pushGLStates();
	window2d->draw(_text);
	window2d->popGLStates();
}

void Window::setFramerateLimit(int fps)
{
	//Set the frames per second rate for the window.
	if (!window2d)
	{
		std::cout << "I can't set the framerate limit -- window2d doesn't exist!\n"; //Error.
		return; //Abort this function.
	}

	window2d->setFramerateLimit(fps);
}

void Window::showMouseCursor(bool show)
{
	//Set the frames per second rate for the window.
	if (!window2d)
	{
		std::cout << "I can't show or hide the mouse cursor -- window2d doesn't exist!\n"; //Error.
		return; //Abort this function.
	}

	window2d->setMouseCursorVisible(show);
}


void Window::setActive()
{
	window2d->setActive(true);
}

} //namespace mgfx

} //namespace GEngine.
