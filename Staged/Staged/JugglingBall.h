#pragma once

#include <SFML/Graphics.hpp>

#include "Globals.h"

class JugglingBall {
public:
	JugglingBall();
	~JugglingBall();

	bool tryClick(sf::Vector2f t_mousePos);
	bool isDropped() const { return m_isDropped; }
	
	void update(sf::Time t_dT);

	void draw(std::shared_ptr<sf::RenderWindow> t_window);

private:
	static constexpr float HORIZONTAL_SPEED = 0.015f;
	static constexpr float MIN_CATCH_HEIGHT = 600.f;
	inline static const sf::Vector2f GRAVITY{ 0.f, 0.02f };

	sf::CircleShape m_shape;
	sf::CircleShape m_glow;

	sf::Vector2f m_velocity{ 0.0f,0.0f };

	bool m_movingLeft;

	bool m_isDropped{ false };
};
