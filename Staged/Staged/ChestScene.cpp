#include "ChestScene.h"

ChestScene::ChestScene()
{
	setupMasks();
}

ChestScene::~ChestScene()
{
}

void ChestScene::setupMasks()
{
	m_masks[0] = &m_mask1;
	m_masks[1] = &m_mask2;
	m_masks[2] = &m_mask3;

	m_mask1.setFillColor(sf::Color::Red);
	m_mask2.setFillColor(sf::Color::Green);
	m_mask3.setFillColor(sf::Color::Blue);

	m_mask1.setPosition({ 430.f, 540.f });
	m_mask2.setPosition({ 860.f, 540.f });
	m_mask3.setPosition({ 1290.f, 540.f });

	for (auto* mask : m_masks) {
		mask->setRadius(100.f);
		mask->setOrigin({ 100.f, 100.f });
	}
}

void ChestScene::processEvents()
{
	while (const std::optional e = m_window->pollEvent())
	{
		if (e->is<sf::Event::Closed>()) { m_window->close(); }
		else if (e->is<sf::Event::KeyPressed>()) { processKeys(e); }
		else if (e->is<sf::Event::MouseButtonPressed>()) { processClick(e); }
	}
	if (m_changeScene) {
		SceneManager::getInstance()->setScene(m_changeSceneTo);
		m_changeScene = false;
	}
}

void ChestScene::processClick(const std::optional<sf::Event> t_event)
{
	sf::Vector2i clickPos = sf::Mouse::getPosition(*m_window.get());
	sf::Vector2f mouseCoords = static_cast<sf::Vector2f>(clickPos);

	auto isClicked = [mouseCoords](sf::CircleShape* mask) -> bool {
		if (!mask) return false;

		sf::Vector2f diff = mouseCoords - mask->getPosition();
		float distanceSq = (diff.x * diff.x) + (diff.y * diff.y);
		float radius = mask->getRadius();

		return distanceSq < (radius * radius);
		};

	for (size_t i = 0; i < m_masks.size(); ++i) {
		if (isClicked(m_masks[i])) {
			m_changeScene = true;

			switch (i) {
			case 0:
				m_changeSceneTo = SceneType::GAMEPLAY;
				break;
			case 1:
				m_changeSceneTo = SceneType::CIRCUS;
				break;
			case 2:
				// action for the 3rd mask
				break;
			}
		}
	}
}

void ChestScene::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed* newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_window->close();
	}
}

void ChestScene::update(sf::Time t_dT)
{
}

void ChestScene::render()
{
	m_window->clear(sf::Color::White);

	for (auto* m : m_masks) {
		m_window->draw(*m);
	}

	m_window->display();
}
