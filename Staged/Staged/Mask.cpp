#include "Mask.h"

void Mask::setMaskDimensions()
{
	maskSprite.setFillColor(sf::Color(150, 50, 250));
	maskSprite.setOrigin(sf::Vector2f{ 25.0f, 25.0f });
	maskSprite.setPosition(sf::Vector2f{ 1920 / 2, 1080 / 2 });
}
