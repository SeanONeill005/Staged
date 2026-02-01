#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "TextureManager.h"

class JugglingBall {
public:
	JugglingBall();
	~JugglingBall();
	bool tryClick(sf::Vector2f t_mousePos);
	bool isDropped() const { return m_isDropped; }

	void update(sf::Time t_dT);
	void draw(std::shared_ptr<sf::RenderWindow> t_window);

private:
	static constexpr float HORIZONTAL_SPEED = 50.f;
	static constexpr float MIN_CATCH_HEIGHT = 500.f;
	static constexpr float BALL_RADIUS = 40.f;
	inline static const sf::Vector2f GRAVITY{ 0.f, 80.f };
	sf::Sprite m_sprite;
	sf::CircleShape m_glow;
	sf::Vector2f m_velocity{ 0.0f, 0.0f };
	float m_rotationSpeed{ 0.f };
	float m_currentRotation{ 0.f };
	bool m_movingLeft;
	bool m_isDropped{ false };

	void randomizeRotation();
};