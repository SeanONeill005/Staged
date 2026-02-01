#include "MainMenuScene.h"

MainMenuScene::MainMenuScene()
	: backgroundSprite(TextureManager::getInstance().get(Textures::Backgrounds::Theatre))
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
		SceneManager::getInstance()->setScene(SceneType::CHEST);
	}
}

void MainMenuScene::processClick(const std::optional<sf::Event> t_event)
{
	const sf::Event::MouseButtonPressed* newMousePress = t_event->getIf<sf::Event::MouseButtonPressed>();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (playButton.getGlobalBounds().contains(m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window))))
		{
			std::cout << "Play Button Clicked" << "\n";
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
	if (playButton.getGlobalBounds().contains((m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)))))
	{
		playButtonSprite.setTexture(playeButtonHighlightedTexture);
	}
	else
	{
		playButtonSprite.setTexture(playButtonTexture);
	}
	if (exitButton.getGlobalBounds().contains((m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)))))
	{
		exitButtonSprite.setTexture(exitButtonHighlightedTexture);
	}
	else
	{
		exitButtonSprite.setTexture(exitButtonTexture);
	}
}

void MainMenuScene::render()
{
	m_window->clear(sf::Color::White);
	m_window->draw(playButton);
	m_window->draw(exitButton);
	m_window->draw(backgroundSprite);
	
	m_window->draw(playText);
	m_window->draw(exitText);
	m_window->draw(exitButtonSprite);
	m_window->draw(playButtonSprite);
}

void MainMenuScene::setupButtons()
{
	playButton.setSize(sf::Vector2f{ 650.0f, 325.0f });
	playButton.setFillColor(sf::Color{ 10, 10, 10 });
	playButton.setOrigin(sf::Vector2f{ playButton.getSize().x / 2, playButton.getSize().y / 2 });
	playButton.setPosition(sf::Vector2f{ (WINDOW_WIDTH / 2) + 15, (WINDOW_HEIGHT / 2) - 95 });

	playText.setString("Play Game");
	playText.setFillColor(sf::Color::White);
	playText.setCharacterSize(75);
	playText.setPosition(playButton.getPosition());
	playText.setPosition(sf::Vector2f(playButton.getPosition().x - 135, playButton.getPosition().y - 50));

	exitButton.setSize(sf::Vector2f{ 650.0f, 315.0f });
	exitButton.setFillColor(sf::Color{ 10, 10, 10, });
	exitButton.setOrigin(sf::Vector2f{ exitButton.getSize().x / 2, exitButton.getSize().y / 2 });
	exitButton.setPosition(sf::Vector2f{ playButton.getPosition().x, 845 });

	exitText.setString("Quit Game");
	exitText.setFillColor(sf::Color::White);
	exitText.setCharacterSize(75);
	exitText.setPosition(sf::Vector2f{ exitButton.getPosition().x - 135, exitButton.getPosition().y - 50 });

	playButtonSprite.setPosition(sf::Vector2f{ 1920 / 2, 0 });
	playButtonSprite.setOrigin(sf::Vector2f{ 1920, 1080 });
	playButtonSprite.setScale(sf::Vector2f{ 0.20, 0.20 });

	exitButtonSprite.setPosition(sf::Vector2f{1920 / 2, 400});
	exitButtonSprite.setOrigin(sf::Vector2f{ 1920, 1080 });
	exitButtonSprite.setScale(sf::Vector2f{ 0.20, 0.20 });
}