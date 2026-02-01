#pragma once
#include "SceneManager.h"
#include "BaseScene.h"
#include "TextureManager.h"
#include "Globals.h"
#include "ScoreManager.h"

class GameOverScene : public BaseScene
{
public:
	GameOverScene();
	~GameOverScene();
	virtual void processEvents() override;
	virtual void update(sf::Time t_dT) override;
	virtual void render() override;

private:
	void setupSprites();
	void setupTexts();
	void processKeys(const std::optional<sf::Event> t_event);
	void processClick(const std::optional<sf::Event> t_event);
	void updateNameDisplay();
	void saveScoreAndReturn();

	sf::Sprite m_theatreBackgroundSprite;
	sf::Font m_scoreFont{ "ASSETS/FONTS/NeonLight-Regular.ttf" };
	sf::Text m_gameOverText{ m_scoreFont };
	sf::Text m_westernScoreText{ m_scoreFont };
	sf::Text m_circusScoreText{ m_scoreFont };
	sf::Text m_totalScoreText{ m_scoreFont };
	sf::Text m_bestWesternText{ m_scoreFont };
	sf::Text m_bestCircusText{ m_scoreFont };
	sf::Text m_bestTotalText{ m_scoreFont };
	sf::Text m_namePromptText{ m_scoreFont };
	sf::Text m_nameInputText{ m_scoreFont };
	sf::Text m_pressKeyText{ m_scoreFont };

	std::string m_playerName = "AAA";
	int m_currentLetterIndex = 0;
	bool m_returnToMenu{ false };
	bool m_scoreSaved{ false };
};