#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SceneManager.h"
#include "BaseScene.h"
#include "Stage.h"
#include "Mask.h"
#include "TextureManager.h"

class WesternScene : public BaseScene
{
public:
	WesternScene();
	~WesternScene();
	virtual void processEvents() override;
	virtual void update(sf::Time t_dT) override;
	virtual void render() override;

private:
	void setupTexts();
	void setupSprites();
	void processKeys(const std::optional<sf::Event> t_event);
	void processClick(const std::optional<sf::Event> t_event);
	void setRandomPosition();
	float getTargetSpeed();
	void showHitMarker(sf::Vector2f position);
	void setCowboyDirection(bool facingLeft);

	// Sprites
	sf::Sprite m_theatreBackgroundSprite;
	sf::Sprite m_westernBackgroundSprite;
	sf::Sprite playerSprite;
	sf::Sprite cactusSprite1;
	sf::Sprite cactusSprite2;
	sf::Sprite targetSprite;
	sf::Sprite hitMarkerSprite;

	// Fonts and Text
	sf::Font m_jerseyFont;
	sf::Font scoreFont{ "ASSETS/FONTS/NeonLight-Regular.ttf" };
	sf::Text m_DELETEwelcomeMessage{ m_jerseyFont };
	sf::Text scoreText{ scoreFont };
	sf::Text missedText{ scoreFont };

	// Timers
	sf::Clock gameTimer;
	sf::Clock animationTimer;
	sf::Time maxTime = sf::seconds(initialTargetTime);
	sf::Time elapsedTime = sf::seconds(0);
	sf::Time animationDuration = sf::seconds(0.25f);

	// Game State
	bool gameCompleted = false;
	bool isAnimating = false;
	bool showingHitMarker = false;
	bool m_cowboyFacingLeft = true;
	SceneType m_setSceneTo;

	// Scores and Stats
	int score = 0;
	int missedTargets = 0;

	// Constants
	const float maxRadius = 50.f;
	const float initialTargetTime = 5.0f;
	const float minimumTargetTime = 1.5f;
	const int maxMissedTargets = 3;
	const float edgeMargin = 150.f;

	// Other Variables
	float currentScale = 1.0f;
};