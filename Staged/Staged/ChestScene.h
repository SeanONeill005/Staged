#pragma once

#include <array>

#include <SFML/Graphics.hpp>

#include "SceneManager.h"
#include "BaseScene.h"

class ChestScene :
	public BaseScene
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

	sf::RectangleShape m_chest;

	sf::CircleShape m_mask1;
	sf::CircleShape m_mask2;
	sf::CircleShape m_mask3;

	std::array<sf::CircleShape*, 3> m_masks;

	bool m_changeScene{ false };
	SceneType m_changeSceneTo;
};