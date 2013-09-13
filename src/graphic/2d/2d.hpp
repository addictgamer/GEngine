/* Please refer to license.txt */

#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "../graphic.hpp"

namespace GEngine
{

namespace mgfx
{

class Window; //Forward declaration.

namespace d2d
{

class D2D
{
public:
	Window *window; //The window being used with this. //NOTE: Please do NOT change this at runtime. Create a new d2d for every window.

	D2D();
	~D2D();

	//Sets up the 2D manager thingy.
	bool setup();

	//Be sure to call setWindow() before using this!
	bool setWindow(Window &_window);

	//Updates the 2D manager thingy.
	void update();
};

class Sprite
{
private:
	sf::Texture *texture; //This is the texture that sf::Sprite *sprite uses.

	float *x, *y; //The x and y of the sprite. Points to the x and y in sf::Sprite sprite; //NOTE: ALWAYS set these using setx and sety.

	//These variables should be set to false if using pointx and its complements so that the pointers do not get deleted (x & y not owned by the sprite) or to true if using setx and its complements (x & y owned by the sprite)
	bool delete_x;
	bool delete_y;

public:
	D2D *d2d; //Pointer to its parent d2d.

	sf::Sprite *sprite; //The actual sprite. NEVER directly set sprite's position. Use setx and sety.

	Sprite();
	~Sprite();

	void draw(); //Draw it.
	void draw(D2D &_d2d); //Draw it with a custom d2d.
	void draw(float _x, float _y); //Draw it with custom coordinates.
	void draw(D2D &_d2d, float _x, float _y); //Draw it with a custom d2d and custom coordinates.
	void drawAsObject();

	/*
	Loads the sprite from a file.
	Parameters:
		std::string filepath : the path to the file to use.
	*/
	bool loadFromFile(std::string filepath);

	void setx(float _x); //Sets x.
	void sety(float _y); //Sets y.
	void setLoc(float _x, float _y); //Sets the x and the y at the same time.
	void pointx(float &_x);
	void pointy(float &_y);
	void pointLoc(float &_x, float &_y);

	float getx(); //Returns the x.
	float gety(); //Returns the y.

	//Return the width and the height.
	int getWidth();
	int getHeight();

	/*
	Moves the sprite.
	Parameters:
		float xmove : the amount to move along the x axis. Positive right, negative left.
		float ymove : the amount to move along the y axis. Positive down, negative up.
	*/
	void move(float xmove, float ymove);

	/*
	Returns a pointer to the texture.
	NOTE: Do NOT use this unless you know what you are doing. The sf::Sprite sprite member should suffice for most stuff.
	*/
	sf::Texture *getTexture();

	/*
	Copies the sprite into the referenced sprite.
	NOTE: Please pass an empty sprite.
	Parameters:
		Sprite &sprite : reference to the sprite to copy into.
	*/
	void copyTo(Sprite &_sprite);
};

//IMAGE MANIPULATION STUFF.

void makeGrayscale(Sprite &sprite); //Makes the specified sprite black and white.

void invertColor(Sprite &sprite); //Invert the specified sprite's color.

} //namespace d2d

} //namespace mgfx

} //namespace GEngine
