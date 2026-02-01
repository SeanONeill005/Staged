#pragma once
#include <stack>

#include "Globals.h"
#include <SFML/Graphics.hpp>
#include "SceneManager.h"
#include "ScoreManager.h"
#include "BaseScene.h"
#include "JugglingBall.h"
#include "TextureManager.h"

class CircusScene : public BaseScene
{
public:
	CircusScene();
	~CircusScene();
	virtual void processEvents() override;
	virtual void update(sf::Time t_dT) override;
	virtual void render() override;

private:
	void setupSprites();
	void setupTexts();
	void processKeys(const std::optional<sf::Event> t_event);
	void processClick(const std::optional<sf::Event> t_event);
	void switchClownJuggleTexture();
	void switchClownPoseTexture();
	void updateScore();

	sf::Sprite m_theatreBackgroundSprite;
	sf::Sprite m_circusBackgroundSprite;
	sf::Sprite m_clownSprite;
	sf::Sprite m_popcornSprite;
	std::vector<JugglingBall> m_jugglingBalls;
	sf::Time m_elapsedTime;
	std::stack<float> m_ballTimes;
	int m_droppedBalls{ 0 };
	int m_lives{ 3 };
	int m_score{ 0 };
	bool m_changeScene{ false };
	SceneType m_changeSceneTo;
	bool m_usingJuggle1{ true };
	bool m_usingPose1{ true };

	sf::Font m_scoreFont{ "ASSETS/FONTS/NeonLight-Regular.ttf" };
	sf::Text m_scoreText{ m_scoreFont };
	sf::Text m_livesText{ m_scoreFont };
};