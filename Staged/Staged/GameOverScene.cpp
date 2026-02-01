#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::processEvents()
{
	while (const std::optional e = m_window->pollEvent())
	{
		if (e->is<sf::Event::Closed>()) { m_window->close(); }
		else if (e->is<sf::Event::KeyPressed>()) { processKeys(e); }
		else if (e->is<sf::Event::MouseButtonPressed>()) { processClick(e); }
	}
}

void GameOverScene::processClick(const std::optional<sf::Event> t_event)
{
	const sf::Event::MouseButtonPressed* newMousePress = t_event->getIf<sf::Event::MouseButtonPressed>();
}

void GameOverScene::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed* newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_window->close();
	}
}

void GameOverScene::update(sf::Time t_dT)
{
}

void GameOverScene::render()
{
	m_window->clear(sf::Color::White);

	m_window->display();
}
