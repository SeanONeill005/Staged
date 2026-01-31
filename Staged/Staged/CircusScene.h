#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

#include "SceneManager.h"
#include "BaseScene.h"

#include "JugglingBall.h"

class CircusScene :
	public BaseScene
{
public:
	CircusScene();
	~CircusScene();

	virtual void processEvents() override;

	virtual void update(sf::Time t_dT) override;

	virtual void render() override;
private:
	void processKeys(const std::optional<sf::Event> t_event);
	void processClick(const std::optional<sf::Event> t_event);

	sf::Texture m_backgroundTexture{ "ASSETS/IMAGES/TheatreBackground.png" };
	sf::Sprite m_backgroundSprite{ m_backgroundTexture };

	std::vector<JugglingBall> m_jugglingBalls;

	sf::Time m_elapsedTime;

	std::stack<float> m_ballTimes;
};