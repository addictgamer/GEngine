/* Please refer to license.txt */

#include "2d.hpp"

#include "../window/window.hpp"

#include <iostream>

namespace GEngine
{

namespace mgfx
{

namespace d2d
{

Sprite::Sprite()
{
	d2d = nullptr;

	x = new float;
	*x = 0;
	y = new float;
	*y = 0;

	delete_x = true;
	delete_y = true;

	texture = nullptr;
	sprite = nullptr;
}

Sprite::~Sprite()
{
	d2d = nullptr; //Nullify it.

	//Delete and unpoint if sprite exists.
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}

	//Delete this second, if it exists, to avoid any and all possible problems when the sprite is freed because it has a reference to this.
	if (texture)
	{
		delete texture;
		texture = nullptr;
	}

	if (x && delete_x)
	{
		delete x; //Delete x, if it exists.
		x = nullptr; //Reset it.
	}

	if (y && delete_y)
	{
		delete y; //Delete y.
		y = nullptr; //Reset it.
	}
}

bool Sprite::loadFromFile(std::string filepath)
{
	//Allocate memory for these two and assign to default.
	if (delete_x)
	{
		if (!x && delete_x)
		{
			x = new float;
			std::cout << "Set x.\n";
		}
		*x = 0;
	}

	if (delete_y)
	{
		if (!y)
		{
			y = new float;
			std::cout << "Set y.\n";
		}
		*y = 0;
	}

	//If the sprite exists, delete it.
	if (sprite)
	{
		delete sprite;
	}
	sprite = new sf::Sprite; //Allocate new memory for the sprite.

	//If the texture exists, delete it.
	if (texture)
	{
		delete texture;
	}
	texture = new sf::Texture; //Allocate new memory for it.

	if (!texture->loadFromFile(filepath)) //Load the sprite.
	{
		std::cout << "*** mgfx::d2d::Sprite::loadFromFile() *** FATAL ERROR: Could not load sprite.\n";
		return false;
	}

	sprite->setTexture(*texture); //Set the sprite's texture.

	return true; //Success.
}

void Sprite::draw()
{
	//If the d2d doesn't exist, something went horribly wrong. Or somebody's using this horribly wrong.
	if (!d2d)
	{
		std::cout << "*** mgfx::d2d::Sprite::draw() *** FATAL ERROR: Variable d2d does not exist on line "  << __LINE__ << " in file \"" << __FILE__ << "\".\n";
		throw;
	}
	else if (!d2d->window)
	{
		std::cout << "*** mgfx::d2d::Sprite::draw() *** FATAL ERROR: Variable window does not exist on line "  << __LINE__ << " in file \"" << __FILE__ << "\".\n";
		throw;
	}

	//We have to push the opengl states before drawing and then pop them afterwards so that CEGUI draws properly.
	d2d->window->window2d->pushGLStates();
	d2d->window->drawSprite(*this); //Draws the sprite.
	d2d->window->window2d->popGLStates();
}

void Sprite::drawAsObject()
{
	draw(); //For now, draw.
}

void Sprite::draw(D2D &_d2d) //Draw it with a custom d2d.
{
	if (!_d2d.window)
	{
		std::cout << "*** mgfx::d2d::Sprite::draw(D2D) *** FATAL ERROR: Variable window does not exist on line "  << __LINE__ << " in file \"" << __FILE__ << "\".\n";
		throw;
	}

	_d2d.window->window2d->pushGLStates();
	_d2d.window->drawSprite(*this);
	_d2d.window->window2d->popGLStates();
}
void Sprite::draw(float _x, float _y) //Draw it with custom coordinates.
{
	//TODO: WARNING: This method of setting x and y might cause trippy results if x and y are simply pointers to another object's x and y.
	//Back up the x and y.
	float tempx = *x;
	float tempy = *y;

	//Set the new x and new y (temporary only).
	setx(_x);
	sety(_y);

	//If the d2d doesn't exist, something went horribly wrong. Or somebody's using this horribly wrong.
	if (!d2d)
	{
		std::cout << "*** mgfx::d2d::Sprite::draw(float, float) *** FATAL ERROR: Variable d2d does not exist on line "  << __LINE__ << " in file \"" << __FILE__ << "\".\n";
		throw;
	}
	else if (!d2d->window)
	{
		std::cout << "*** mgfx::d2d::Sprite::draw() *** FATAL ERROR: Variable window does not exist on line "  << __LINE__ << " in file \"" << __FILE__ << "\".\n";
		throw;
	}

	d2d->window->window2d->pushGLStates();
	d2d->window->drawSprite(*this); //Draws the sprite.
	d2d->window->window2d->popGLStates();

	//Revert x and y back to the old values.
	setx(tempx);
	sety(tempy);
}

void Sprite::draw(D2D &_d2d, float _x, float _y) //Draw it with a custom d2d and custom coordinates.
{
	//TODO: WARNING: This method of setting x and y might cause trippy results if x and y are simply pointers to another object's x and y.
	//Back up the x and y.
	float tempx = *x;
	float tempy = *y;

	//Set the new x and new y (temporary only).
	setx(_x);
	sety(_y);

	if (!_d2d.window)
	{
		std::cout << "***mgfx::d2d::Sprite*** FATAL ERROR: Variable window does not exist on line "  << __LINE__ << " in file \"" << __FILE__ << "\".\n";
		throw;
	}

	_d2d.window->window2d->pushGLStates();
	_d2d.window->drawSprite(*this);
	_d2d.window->window2d->popGLStates();

	//Revert x and y back to the old values.
	setx(tempx);
	sety(tempy);
}

void Sprite::setx(float _x)
{
	if (!delete_x)
	{
		std::cout << "*** mgfx::d2d::Sprite*** FATAL ERROR: mgfx::d2d::Sprite::setx() called when delete_x is false (the sprite doesn't own its x) on line" << __LINE__ << " in file \"" << __FILE__ <<  "\". Aborting\n";
		throw; //TODO: This might be bad idea. Maybe just a warning?
	}

	//x should exist. If it doesn't, then there's been some major error.)
	if (!x)
	{
		std::cout << "*** mgfx::d2d::Sprite::setx() *** FATAL ERROR: Variable x does not exist on line "  << __LINE__ << " in file \"" << __FILE__ << "\".\n";
		throw;
	}

	*x = _x; //Assign x.

	sprite->setPosition(*x, *y); //Set the position.
}

void Sprite::sety(float _y)
{
	if (!delete_y)
	{
		std::cout << "*** mgfx::d2d::Sprite*** FATAL ERROR: mgfx::d2d::Sprite::sety() called when delete_y is false (the sprite doesn't own its y) on line" << __LINE__ << " in file \"" << __FILE__ <<  "\". Aborting\n";
		throw; //TODO: This might be bad idea. Maybe just a warning?
	}

	//y should exist. If it doesn't then there's been some major error.
	if (!y)
	{
		std::cout << "*** mgfx::d2d::Sprite::sety() *** FATAL ERROR: Variable y does not exist on line "  << __LINE__ << " in file \"" << __FILE__ << "\".\n";
		throw;
	}

	*y = _y; //Assign y.

	sprite->setPosition(*x, *y); //Set the position.
}

void Sprite::setLoc(float _x, float _y)
{
	if (!delete_x)
	{
		std::cout << "*** mgfx::d2d::Sprite*** FATAL ERROR: mgfx::d2d::Sprite::setx() called when delete_x is false (the sprite doesn't own its x) on line" << __LINE__ << " in file \"" << __FILE__ <<  "\". Aborting\n";
		throw; //TODO: This might be bad idea. Maybe just a warning?
	}
	if (!delete_y)
	{
		std::cout << "*** mgfx::d2d::Sprite*** FATAL ERROR: mgfx::d2d::Sprite::sety() called when delete_y is false (the sprite doesn't own its y) on line" << __LINE__ << " in file \"" << __FILE__ <<  "\". Aborting\n";
		throw; //TODO: This might be bad idea. Maybe just a warning?
	}

	if (!x || !y)
	{
		std::cout << "*** mgfx::d2d::Sprite::setLoc() *** FATAL ERROR: Variable " << ((!x) ? "x" : "y") << " does not exist.\n";
		throw;
	}

	*x = _x;
	*y = _y;

	sprite->setPosition(*x, *y);
}

void Sprite::pointx(float &_x)
{
	if (delete_x)
	{
		delete x;
	}

	delete_x = false;

	x = &_x; //Point to x.

	sprite->setPosition(*x, *y); //Set the position.
}

void Sprite::pointy(float &_y)
{
	if (delete_y)
	{
		delete y;
	}

	delete_y = false;

	y = &_y; //Point to y.

	sprite->setPosition(*x, *y); //Set the position.
}

void Sprite::pointLoc(float &_x, float &_y)
{
	if (delete_x)
	{
		delete x;
	}

	delete_x = false;

	if (delete_y)
	{
		delete y;
	}

	delete_y = false;

	x = &_x;
	y = &_y;

	sprite->setPosition(*x, *y);
}

float Sprite::getx()
{
	return *x;
}

float Sprite::gety()
{
	return *y;
}

int Sprite::getWidth()
{
	return sprite->getTexture()->getSize().x;
}

int Sprite::getHeight()
{
	return sprite->getTexture()->getSize().y;
}

void Sprite::move(float xmove, float ymove)
{
	//Update x and y.
	*x += xmove;
	*y += ymove;

	sprite->setPosition(*x, *y);
}

sf::Texture *Sprite::getTexture()
{
	return texture;
}

void Sprite::copyTo(Sprite &_sprite)
{
	//Texture and sprite first.
	_sprite.sprite = new sf::Sprite; //Allocate memory.
	_sprite.texture = new sf::Texture(*texture); //Allocate memory for the texture with the copy constructor to copy the texture's pixels.
	//Assign the texture to the sf::Sprite.
	_sprite.sprite->setTexture(*_sprite.texture);

	//Now coordinates.
	_sprite.setLoc(*x, *y);

	//Set the d2d.
	_sprite.d2d = d2d;
}

} //namespace d2d

} //namespace mgfx

} //namespace GEngine
