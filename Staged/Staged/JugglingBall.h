#pragma once

#include <SFML/Graphics.hpp>

class JugglingBall {
public:
	JugglingBall();
	~JugglingBall() = default;

	bool tryClick(sf::Vector2f t_mousePos);
	
	void update(sf::Time t_dT);

	void draw(std::shared_ptr<sf::RenderWindow> t_window);

private:
	const sf::Vector2f GRAVITY{ 0.f, 0.02f };
	const float HORIZONTAL_SPEED = 0.015f;

	const float MIN_CATCH_HEIGHT = 600.f;

	sf::CircleShape m_shape;
	sf::CircleShape m_glow;

	sf::Vector2f m_velocity{ 0.0f,0.0f };

	bool m_movingLeft;
};
