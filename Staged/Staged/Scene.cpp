#include "Scene.h"

void Scene::setSceneDimensions()
{
	sceneSprite.setSize(sf::Vector2f{1000.0f, 500.0f});
	sceneSprite.setOrigin(sf::Vector2f{ 500.0f, 250.0f });
	sceneSprite.setPosition(sf::Vector2f{ 1920 / 2,1080 / 2 });
}