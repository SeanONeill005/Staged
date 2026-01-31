#include "CircusScene.h"

CircusScene::CircusScene() 
	: m_ballTimes(std::deque<float>{10.f, 7.f, 5.f, 3.f, 0.f})
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\TheatreBackground.png"))
	{
		std::cout << "problem loading logo" << std::endl;
	}

	m_backgroundSprite.setTexture(m_backgroundTexture, true);
}

CircusScene::~CircusScene()
{
}

void CircusScene::processEvents()
{
	while (const std::optional e = m_window->pollEvent())
	{
		if (e->is<sf::Event::Closed>()) { m_window->close(); }
		else if (e->is<sf::Event::KeyPressed>()) { processKeys(e); }
		else if (e->is<sf::Event::MouseButtonPressed>()) { processClick(e); }
	}
}

void CircusScene::processClick(const std::optional<sf::Event> t_event)
{
	sf::Vector2i clickPos = sf::Mouse::getPosition(*m_window.get());
	sf::Vector2f mouseCoords = static_cast<sf::Vector2f>(clickPos);

	for (auto& ball : m_jugglingBalls) {
		ball.tryClick(mouseCoords);
	}
}

void CircusScene::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed* newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_window->close();
	}
}

void CircusScene::update(sf::Time t_dT)
{
	for (auto& ball : m_jugglingBalls) {
		ball.update(t_dT);

		if (ball.isDropped()) {
			m_droppedBalls++;
			std::cout << "You dropped the ball :(" << std::endl;
		}
	}

	m_jugglingBalls.erase(
		std::remove_if(m_jugglingBalls.begin(), m_jugglingBalls.end(),
			[](const JugglingBall& ball) {
				return ball.isDropped();
			}),
		m_jugglingBalls.end()
	);


	m_elapsedTime += t_dT;

	if (!m_ballTimes.empty()) {
		if (m_elapsedTime.asSeconds() > m_ballTimes.top()) {
			JugglingBall ball;
			m_jugglingBalls.push_back(ball);

			m_ballTimes.pop();
		}
	}
}

void CircusScene::render()
{
	m_window->clear(sf::Color::White);

	m_window->draw(m_backgroundSprite);

	for (auto& ball : m_jugglingBalls) {
		ball.draw(m_window);
	}

	m_window->display();
}
