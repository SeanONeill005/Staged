#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Mask
{
public:
	Mask(std::string type) : type(type) {}

	std::string getMaskType()
	{
		return type;
	}

	void setMaskDimensions();

	sf::CircleShape getMaskSprite()
	{
		return maskSprite;
	}
private:
	std::string type;
	sf::CircleShape maskSprite{ 50.0f };
};