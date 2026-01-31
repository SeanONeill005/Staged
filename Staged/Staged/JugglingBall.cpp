#include "JugglingBall.h"

JugglingBall::JugglingBall()
{
	m_movingLeft = rand() % 2;

	int r = 0;
	int g = std::rand() % 256;
	int b = std::rand() % 256;

	m_shape.setFillColor(sf::Color(r,g,b));
	m_shape.setRadius(40.f);
	m_shape.setOrigin({ 40.f,40.f });

	m_glow.setFillColor(sf::Color::Yellow);
	m_glow.setRadius(50.f);
	m_glow.setOrigin({ 50.f,50.f });

	if (m_movingLeft) {
		m_shape.setPosition({ 800.f, 200.f });
	}
	else {
		m_shape.setPosition({ 1100.f, 200.f });
	}
}

bool JugglingBall::tryClick(sf::Vector2f t_mousePos)
{
	if (m_velocity.y < 0 || m_shape.getPosition().y < MIN_CATCH_HEIGHT) {
		return false;
	}

	sf::Vector2f diff = t_mousePos - m_shape.getPosition();
	float distanceSq = (diff.x * diff.x) + (diff.y * diff.y);
	float radius = m_shape.getRadius();

	if (distanceSq < (radius * radius)) {
		float horizontalSpeed = m_movingLeft ? HORIZONTAL_SPEED : -HORIZONTAL_SPEED;
		m_movingLeft = !m_movingLeft;

		m_velocity = { horizontalSpeed, -0.08f };
		return true;
	}

	return false;
}

void JugglingBall::update(sf::Time t_dT)
{
	m_velocity += GRAVITY * t_dT.asSeconds();
	m_shape.move(m_velocity);
}

void JugglingBall::draw(std::shared_ptr<sf::RenderWindow> t_window)
{
	if (m_velocity.y > 0 && m_shape.getPosition().y > MIN_CATCH_HEIGHT) {
		m_glow.setPosition(m_shape.getPosition());
		t_window->draw(m_glow);
	}

	t_window->draw(m_shape);
}
