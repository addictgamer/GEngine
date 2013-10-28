/* Please refer to license.txt */

#pragma once

#include <string>

// Should it #include "../graphic.hpp" ?

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "../graphic.hpp"

//TODO: SFML graphics module and opengl drawing support.
//SFML supports it, this thing will need to wrap it correctly and stuff.

namespace GEngine
{

namespace mgfx
{

namespace d2d
{

class D2D;
class Sprite;

}

class Window
{
public:
	d2d::D2D *parent_d2d; //Pointer to the parent d2d.

	//Window width and height.
	int *width, *height;
	//Are the width and height to be deleted in the deconstructor, or merely set to nullptr?
	bool delete_width, delete_height;

	//Window is fullscreen?
	bool fullscreen;

	//The window's name.
	std::string windowname;

	//The actual window.
	//A SFML window. Used for OpenGL. Use window2d for 2d rendering. Use this one with OpenGL.
	//NOTE: If it's closed somewhere outside the deconstructor, delete it there (and set it to nullptr, and set closed to true) too.
	//sf::Window *window3d;
	//2D rendering version of the above. Do not use with OpenGL. Use the above for OpenGL. use this for 2D SFML drawing.
	sf::RenderWindow *window2d;
	//Event thingy for the window.
	sf::Event *event;

	//Is the window open or closed?
	bool closed;
	//Can the window be closed?
	bool can_close;

	//Is the window focused?
	bool focus;

	//Using OpenGL?
	//bool using_opengl;

	//A vector of all events not concerning the window, stored for external processing and cleared every time the window is updated.
	//TODO: It might be a good idea to dump ALL events in here anyway, even the ones that the window handles. We'll see.
	std::vector<sf::Event> events;

	Window();
	~Window();

	/*
	Creates the window.
	Parameters:
		_width : the window's width.
		_height : the window's height.
		_fullscreen : whether or not the window is fullscreen.
		_windowname : the window's name.
		opengl : wether or not to use OpenGL.
			false : (use for 2d SFML drawing) can't use OpenGL contexes with this window (until the point in time switching opengl contexes on and off is implemented).
			true : (use for 3d opengl rendering) can't use SFML drawing until the point in time switching opengl contexes on and off is implemented.
	*/
	bool create(int _width, int _height, bool _fullscreen, std::string _windowname, bool use_opengl);

	//Polls events, handles them, and draws the window.
	void update();

	//Returns the width.
	//Returns -1 on error.
	int getWidth();
	//Returns the height.
	//Returns -1 on error.
	int getHeight();

	//Returns the x of the window.
	int getX();
	//Returns the y of the window.
	int getY();

	/*
	Draws the given sprite onto the screen.
	Parameters:
		d2d::Sprite sprite : the sprite to draw.
	*/
	void drawSprite(mgfx::d2d::Sprite &sprite);

	/*
	Renders the text given to it.
	Parameters:
		std::string text : the text to render.
		int x : the x to render it at.
		int y : the y to render it at.
	*/
	void renderText(std::string text, int _x, int _y, int font_size, sf::Font &font);

	/*
	Limits the FPS of the window.
	Parameters:
		int fps : the maximum frames per second.
	*/
	void setFramerateLimit(int fps);

	/*
	Tells the SFML window to show or hide the system cursor.
	Parameters:
		bool show : true = shows the cursor and false = hide it.
	*/
	void showMouseCursor(bool show);

	/*
	 * Basically a wrapper to SFML's setActive function for windows.
	 */
	void setActive();

	//TODO: Resize function.
};

} //namespace mgfx

} //namespace GEngine
