#include "MainMenuScene.h"

MainMenuScene::MainMenuScene()
{
	setupButtons();
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::processEvents()
{
	while (const std::optional e = m_window->pollEvent())
	{
		if (e->is<sf::Event::Closed>()) { m_window->close(); }
		else if (e->is<sf::Event::MouseButtonPressed>()) { processClick(e); }
		

	}
	if (playPressed)
	{
		playPressed = false;
		SceneManager::getInstance()->setScene(SceneType::GAMEPLAY);
	}
}

void MainMenuScene::processClick(const std::optional<sf::Event> t_event)
{
	const sf::Event::MouseButtonPressed* newMousePress = t_event->getIf<sf::Event::MouseButtonPressed>();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{

		if (playButton.getGlobalBounds().contains(m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window))))
		{
			std::cout << "Play Button CLicked" << "\n";
			playPressed = true;
		}
		else if (exitButton.getGlobalBounds().contains(m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window))))
		{
			std::cout << "Exit Button Clicked" << "\n";
			m_window->close();
		}
	}
}

void MainMenuScene::update(sf::Time t_dT)
{
	processEvents();
}

void MainMenuScene::render()
{
	m_window->clear(sf::Color::White);
	m_window->draw(playButton);
	m_window->draw(exitButton);
	m_window->display();
}

void MainMenuScene::setupButtons()
{
	playButton.setSize(sf::Vector2f{ 400.0f, 200.0f });
	playButton.setFillColor(sf::Color{ 10, 10, 10 });
	playButton.setOrigin(sf::Vector2f{ playButton.getSize().x / 2, playButton.getSize().y / 2 });
	playButton.setPosition(sf::Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });

	exitButton.setSize(sf::Vector2f{ 400.0f, 200.0f });
	exitButton.setFillColor(sf::Color{ 10, 10, 10, });
	exitButton.setOrigin(sf::Vector2f{ exitButton.getSize().x / 2, exitButton.getSize().y / 2 });
	exitButton.setPosition(sf::Vector2f{ playButton.getPosition().x, playButton.getPosition().y + 300 });
}
