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

	void setMaskDimensions(int index);

	sf::CircleShape getMaskSprite()
	{
		return maskSprite;
	}

	void setRandomPosition();

	sf::Vector2f getPosition()
	{
		return maskSprite.getPosition();
	}

private:

	std::string type;
	sf::CircleShape maskSprite{ 50.0f };
};