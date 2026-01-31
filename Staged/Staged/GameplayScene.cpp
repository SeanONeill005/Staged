#include "GameplayScene.h"

GameplayScene::GameplayScene() {
	setupTexts(); // load font 
	setupSprites(); // load texture
}

GameplayScene::~GameplayScene()
{
}

void GameplayScene::processEvents()
{
	while (const std::optional e = m_window->pollEvent())
	{
		if (e->is<sf::Event::Closed>()) { m_window->close(); }
		else if (e->is<sf::Event::KeyPressed>()) { processKeys(e); }
		else if (e->is<sf::Event::MouseButtonPressed>()) { processClick(e); }
	}
}

void GameplayScene::processClick(const std::optional<sf::Event> t_event)
{
	const sf::Event::MouseButtonPressed* newMousePress = t_event->getIf<sf::Event::MouseButtonPressed>();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		std::cout << sf::Mouse::getPosition(*m_window).x << "\n";
		std::cout << sf::Mouse::getPosition(*m_window).y << "\n";

		if (sf::Mouse::getPosition(*m_window).x < clicker.getPosition().x + clicker.getRadius() && sf::Mouse::getPosition(*m_window).x > clicker.getPosition().x - clicker.getRadius() &&
			sf::Mouse::getPosition(*m_window).y < clicker.getPosition().y + clicker.getRadius() && sf::Mouse::getPosition(*m_window).y > clicker.getPosition().y - clicker.getRadius())
		{
			setRandomPosition();
		}
	}
}

/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void GameplayScene::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed* newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_window->close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		setRandomPosition();
	}

}

void GameplayScene::update(sf::Time t_dT)
{
	elapsedTime += t_dT;
	if (elapsedTime > maxTime) {
		elapsedTime = sf::seconds(0);
	}

	float radius = (1 - (elapsedTime / maxTime)) * maxRadius;
	clicker.setRadius(radius);
	clicker.setOrigin({ radius, radius });
}

void GameplayScene::render()
{
	m_window->clear(sf::Color::White);

	m_window->draw(m_backgroundSprite);

	m_window->draw(clicker);

	m_window->display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void GameplayScene::setupTexts()
{
	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_DELETEwelcomeMessage.setFont(m_jerseyFont);
	m_DELETEwelcomeMessage.setString("SFML Game");
	m_DELETEwelcomeMessage.setPosition(sf::Vector2f{ 205.0f, 240.0f });
	m_DELETEwelcomeMessage.setCharacterSize(96U);
	m_DELETEwelcomeMessage.setOutlineColor(sf::Color::Black);
	m_DELETEwelcomeMessage.setFillColor(sf::Color::Red);
	m_DELETEwelcomeMessage.setOutlineThickness(2.0f);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void GameplayScene::setupSprites()
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\TheatreBackground.png"))
	{
		std::cout << "problem loading logo" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture, true);

	for (int index = 0; index < maskList.size(); index++)
	{
		maskList[index].setMaskDimensions(index);
	}
	stage.setSceneDimensions();
	clicker.setOrigin(sf::Vector2f{ 25.0f, 25.0f });
}

void GameplayScene::setRandomPosition()
{
	float posX = rand() % static_cast<int>(RESOLUTION.x);
	float posY = rand() % static_cast<int>(RESOLUTION.y);
	clicker.setPosition(sf::Vector2f{ posX, posY });
	clicker.setRadius(maxRadius);
	elapsedTime = maxTime;
}
