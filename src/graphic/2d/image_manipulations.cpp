/* Copyright Ciprian Ilies */

#include "2d.hpp"

#include <iostream>

namespace mgfx
{

namespace d2d
{

void makeGrayscale(Sprite &sprite)
{
	if (!sprite.sprite) //Needs to have a sprite.
	{
		//TODO: Use the error module.
		std::cout << "*** mgfx::d2d::makeBlackAndWhite() *** FATAL ERROR: Sprite requires sf::Sprite\n";
		throw;
	}

	sf::Image image = sprite.getTexture()->copyToImage();

	for (int x = 0; x < sprite.getWidth(); ++x)
	{
		for (int y = 0; y < sprite.getHeight(); ++y)
		{
			sf::Color color = image.getPixel(x, y);
			unsigned int gray = (color.r + color.g + color.b) / 3;
			color.r = gray;
			color.g = gray;
			color.b = gray;
			image.setPixel(x, y, color);
		}
	}

	sprite.getTexture()->update(image);
}

void invertColor(Sprite &sprite) //Invert the specified sprite's color.
{
	if (!sprite.sprite) //Needs to have a sprite.
	{
		//TODO: Use the error module.
		std::cout << "*** mgfx::d2d::invertColor() *** FATAL ERROR: Sprite requires sf::Sprite\n";
		throw;
	}

	sf::Image image = sprite.getTexture()->copyToImage();

	for (int x = 0; x < sprite.getWidth(); ++x)
	{
		for (int y = 0; y < sprite.getHeight(); ++y)
		{
			sf::Color color = image.getPixel(x, y);
			color.r = 255 - color.r;
			color.g = 255 - color.g;
			color.b = 255 - color.b;
			image.setPixel(x, y, color);
		}
	}

	sprite.getTexture()->update(image);
}

} //namespace d2d

} //namespace d2d
