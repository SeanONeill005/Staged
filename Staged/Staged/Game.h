#ifndef GAME_H
#define GAME_H

#include <array>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "TextureManager.h"
#include "WesternScene.h"
#include "CircusScene.h"
#include "BoatScene.h"
#include "ChestScene.h" 
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"

class Game
{
public:

	Game() = default;
	~Game() = default;

	void run();

private:

	void init();

	void loadTextures();

	std::shared_ptr<sf::RenderWindow> m_window;
};
#endif