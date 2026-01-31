#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "SceneManager.h"
#include "BaseScene.h"
#include "Stage.h"
#include "Mask.h"

class GameplayScene :
    public BaseScene
{
public:
    GameplayScene();
    ~GameplayScene();

    virtual void processEvents() override;

    virtual void update(sf::Time t_dT) override;

    virtual void render() override;

private:
	void setupTexts();
	void setupSprites();
	void setupAudio();

	void processKeys(const std::optional<sf::Event> t_event);
	void processClick(const std::optional<sf::Event> t_event);

	void setRandomPosition();

	sf::Font m_jerseyFont;

	sf::Text m_DELETEwelcomeMessage{ m_jerseyFont };
	sf::Texture m_backgroundTexture{ "ASSETS/IMAGES/TheatreBackground.png" };
	sf::Sprite m_backgroundSprite{ m_backgroundTexture };

	Mask mask = "Blue";
	Mask maskRed = "Red";
	Stage stage = "Purple";

	std::vector<Mask> maskList = { mask, maskRed };

	const float maxRadius = 50.f;
	sf::CircleShape clicker{ 50.0f };

	sf::Time maxTime = sf::seconds(5);
	sf::Time elapsedTime = sf::seconds(0);

	bool gameCompleted = false;

	int score = 0;
	sf::Font scoreFont{ "ASSETS/FONTS/Jersey20-Regular.ttf" };
	sf::Text scoreText{ scoreFont };

	sf::Time endTimer = sf::seconds(20);
	sf::Clock gameTimer;
};
