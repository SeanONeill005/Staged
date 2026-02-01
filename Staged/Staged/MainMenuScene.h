#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BaseScene.h"
#include "Globals.h"
#include "SceneManager.h"
#include "TextureManager.h"

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
	sf::Font textFont{ "ASSETS/FONTS/Jersey20-Regular.ttf" };
	sf::Text playText{ textFont };
	sf::Text exitText{ textFont };
	sf::Sprite backgroundSprite;
	sf::Texture playButtonTexture{"ASSETS/IMAGES/PlayButton.png"};
	sf::Texture playeButtonHighlightedTexture{ "ASSETS/IMAGES/PlayHighlighted.png" };
	sf::Sprite playButtonSprite{ playButtonTexture };
	sf::Texture exitButtonTexture{ "ASSETS/IMAGES/QuitButton.png" };
	sf::Texture exitButtonHighlightedTexture{ "ASSETS/IMAGES/QuitHighlighted.png" };
	sf::Sprite exitButtonSprite{ exitButtonTexture };
};