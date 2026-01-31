#include "Mask.h"

void Mask::setMaskDimensions(int index)
{
	maskSprite.setFillColor(sf::Color{ 0,0,0 });
	maskSprite.setOrigin(sf::Vector2f{ 25.0f, 25.0f });
	maskSprite.setPosition(sf::Vector2f{ (1920 / 2) + (100.0f * index), 1080 / 2 });
}

void Mask::setRandomPosition()
{
	float posX = rand() % 1880;
	float posY = rand() % 1030;
	maskSprite.setPosition(sf::Vector2f{ posX, posY });
}