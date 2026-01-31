#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "BaseScene.h"
#include "Globals.h"
#include "SceneManager.h"
class MainMenuScene : public BaseScene
{
public:
	MainMenuScene();
	~MainMenuScene();

	virtual void processEvents() override;

	virtual void update(sf::Time t_dT) override;

	virtual void render() override;

	void setupButtons();

	void processClick(const std::optional<sf::Event> t_event);
private:
	sf::RectangleShape playButton;
	sf::RectangleShape exitButton;
	bool playPressed = false;
};