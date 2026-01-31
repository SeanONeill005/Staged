#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Stage
{
public:
	Stage(std::string type) : type(type) {}

	std::string getSceneType()
	{
		return type;
	}

	sf::RectangleShape getStageSprite()
	{
		return sceneSprite;
	}

	void setSceneDimensions();

private:
	std::string type;
	sf::RectangleShape sceneSprite{ sf::Vector2{120.f, 50.f} };
};