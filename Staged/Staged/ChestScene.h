#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include "SceneManager.h"
#include "BaseScene.h"
#include "TextureManager.h"
#include "Globals.h"

class ChestScene : public BaseScene
{
public:
	ChestScene();
	~ChestScene();
	virtual void processEvents() override;
	virtual void update(sf::Time t_dT) override;
	virtual void render() override;

private:
	void setupMasks();
	void processKeys(const std::optional<sf::Event> t_event);
	void processClick(const std::optional<sf::Event> t_event);

	sf::Sprite m_menuBackgroundSprite;
	sf::Sprite m_chestSprite;
	sf::Sprite m_mask1Sprite;
	sf::Sprite m_mask2Sprite;
	sf::RectangleShape m_greyOverlay1;
	sf::RectangleShape m_greyOverlay2;
	std::array<sf::Sprite*, 2> m_masks;
	bool m_changeScene{ false };
	SceneType m_changeSceneTo;
};
