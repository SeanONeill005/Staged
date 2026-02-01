#include "JugglingBall.h"

JugglingBall::JugglingBall()
	: m_sprite(TextureManager::getInstance().get(Textures::Props::Ball))
{
	m_movingLeft = rand() % 2;

	// Set up sprite
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });

	// Scale sprite to match the 40px radius we want
	float desiredDiameter = BALL_RADIUS * 2.f;
	float scale = desiredDiameter / bounds.size.x;
	m_sprite.setScale({ scale, scale });

	// Random starting rotation
	m_currentRotation = static_cast<float>(rand() % 360);
	m_sprite.setRotation(sf::degrees(m_currentRotation));

	// Randomize rotation speed and direction
	randomizeRotation();

	// Set up glow
	m_glow.setFillColor(sf::Color::Yellow);
	m_glow.setRadius(50.f);
	m_glow.setOrigin({ 50.f, 50.f });

	// Set initial position
	if (m_movingLeft) {
		m_sprite.setPosition({ 800.f, 200.f });
	}
	else {
		m_sprite.setPosition({ 1150.f, 200.f });
	}
}

JugglingBall::~JugglingBall()
{
}

void JugglingBall::randomizeRotation()
{
	float speed = 30.f + static_cast<float>(rand() % 61);
	float direction = (rand() % 2) ? 1.f : -1.f;
	m_rotationSpeed = speed * direction;
}

bool JugglingBall::tryClick(sf::Vector2f t_mousePos)
{
	if (m_velocity.y < 0 || m_sprite.getPosition().y < MIN_CATCH_HEIGHT) {
		return false;
	}
	sf::Vector2f diff = t_mousePos - m_sprite.getPosition();
	float distanceSq = (diff.x * diff.x) + (diff.y * diff.y);

	// Use BALL_RADIUS for collision detection
	if (distanceSq < (BALL_RADIUS * BALL_RADIUS)) {
		float horizontalSpeed = m_movingLeft ? HORIZONTAL_SPEED : -HORIZONTAL_SPEED;
		m_movingLeft = !m_movingLeft;
		m_velocity = { horizontalSpeed, -300.f };

		// Change rotation when ball is clicked
		randomizeRotation();

		return true;
	}
	return false;
}

void JugglingBall::update(sf::Time t_dT)
{
	if (!m_isDropped) {
		if (m_sprite.getPosition().y > RESOLUTION.y + 100) {
			m_isDropped = true;
		}
		m_velocity += GRAVITY * t_dT.asSeconds();
		m_sprite.move(m_velocity * t_dT.asSeconds());

		// Update rotation
		m_currentRotation += m_rotationSpeed * t_dT.asSeconds();
		m_sprite.setRotation(sf::degrees(m_currentRotation));
	}
}

void JugglingBall::draw(std::shared_ptr<sf::RenderWindow> t_window)
{
	if (!m_isDropped) {
		if (m_velocity.y > 0 && m_sprite.getPosition().y > MIN_CATCH_HEIGHT) {
			m_glow.setPosition(m_sprite.getPosition());
			t_window->draw(m_glow);
		}
		t_window->draw(m_sprite);
	}
}
