/* Please refer to license.txt */

#pragma once

#undef interface // For some reason, the Win32 API defined 'interface' as 'struct'... *sigh*

#include <string>

#include <SFML/Graphics.hpp>

namespace GEngine
{

namespace mgfx
{

namespace d2d
{

class D2D;
class Sprite;

} //namespace d2d

class Window;

} //namespace mgfx

namespace mui
{

namespace homebrew
{

class Button
{
private:
	int x, y;
	mgfx::d2d::D2D *d2d; //The 2D interface thingy it resides in.
	//TODO: Sprite.
public:
	Button();
	~Button();

	/*
	 * Initialize the button with everything.
	 */
	void initialize(int arg_x, int arg_y, mgfx::d2d::D2D &arg_d2d); //TODO: Sprite.

	//TODO: Check if it was clicked.
	/*
	 * Checks if the button was left-clicked.
	 * Returns:
	 	* true if clicked
	 	* false if not clicked
	 */
	bool checkLeftClicked();
};

} //namespace homebrew

} //namespace mui

} //namespace GEngine
