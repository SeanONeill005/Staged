#include "CircusScene.h"

CircusScene::CircusScene()
	: m_theatreBackgroundSprite(TextureManager::getInstance().get(Textures::Backgrounds::Theatre))
	, m_circusBackgroundSprite(TextureManager::getInstance().get(Textures::Backgrounds::Circus))
	, m_clownSprite(TextureManager::getInstance().get(Textures::Clown::Juggle1))
	, m_popcornSprite(TextureManager::getInstance().get(Textures::Props::Popcorn))
	, m_ballTimes(std::deque<float>{11.f, 8.f, 6.f, 4.f, 1.f})
{
	setupSprites();
	setupTexts();
}

CircusScene::~CircusScene()
{
}

void CircusScene::setupSprites()
{
	// Set up circus background
	sf::FloatRect circusBounds = m_circusBackgroundSprite.getLocalBounds();
	m_circusBackgroundSprite.setOrigin({ circusBounds.size.x / 2.f, circusBounds.size.y / 2.f });
	m_circusBackgroundSprite.setPosition({ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT * 0.4f });

	// Set up clown sprite
	sf::FloatRect clownBounds = m_clownSprite.getLocalBounds();
	m_clownSprite.setOrigin({ clownBounds.size.x / 2.f, clownBounds.size.y / 2.f });
	m_clownSprite.setScale(sf::Vector2f{ .2f, .2f });
	m_clownSprite.setPosition(sf::Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.6f });

	// Set up popcorn sprite (bottom right corner)
	sf::FloatRect popcornBounds = m_popcornSprite.getLocalBounds();
	m_popcornSprite.setOrigin({ popcornBounds.size.x / 2.f, popcornBounds.size.y });
	m_popcornSprite.setScale({ 0.5f, 0.5f });
	m_popcornSprite.setPosition({ WINDOW_WIDTH - 400.f, WINDOW_HEIGHT - 50.f });
}

void CircusScene::setupTexts()
{
	// Score text
	m_scoreText.setCharacterSize(60);
	m_scoreText.setFillColor(sf::Color::Black);
	m_scoreText.setPosition(sf::Vector2f{ 10.0f, 10.0f });
	m_scoreText.setString("Score: 0");

	// Lives text
	m_livesText.setCharacterSize(60);
	m_livesText.setFillColor(sf::Color::Red);
	m_livesText.setPosition(sf::Vector2f{ 10.0f, 80.0f });
	m_livesText.setString("Lives: 3");
}

void CircusScene::switchClownJuggleTexture()
{
	if (m_usingJuggle1) {
		m_clownSprite.setTexture(TextureManager::getInstance().get(Textures::Clown::Juggle2));
	}
	else {
		m_clownSprite.setTexture(TextureManager::getInstance().get(Textures::Clown::Juggle1));
	}
	m_usingJuggle1 = !m_usingJuggle1;
}

void CircusScene::switchClownPoseTexture()
{
	if (m_usingPose1) {
		m_clownSprite.setTexture(TextureManager::getInstance().get(Textures::Clown::Pose2));
	}
	else {
		m_clownSprite.setTexture(TextureManager::getInstance().get(Textures::Clown::Pose1));
	}
	m_usingPose1 = !m_usingPose1;
}

void CircusScene::updateScore()
{
	// Calculate multiplier based on number of balls in flight
	int activeBalls = static_cast<int>(m_jugglingBalls.size());
	int multiplier = std::max(1, activeBalls);

	// Base points per catch = 10, multiplied by number of balls
	int points = 10 * multiplier;
	m_score += points;

	m_scoreText.setString("Score: " + std::to_string(m_score));
}

void CircusScene::processEvents()
{
	while (const std::optional e = m_window->pollEvent())
	{
		if (e->is<sf::Event::Closed>()) { m_window->close(); }
		else if (e->is<sf::Event::KeyPressed>()) { processKeys(e); }
		else if (e->is<sf::Event::MouseButtonPressed>()) { processClick(e); }
	}
	if (m_changeScene) {
		SceneManager::getInstance()->setScene(m_changeSceneTo);
	}
}

void CircusScene::processClick(const std::optional<sf::Event> t_event)
{
	sf::Vector2i clickPos = sf::Mouse::getPosition(*m_window.get());
	sf::Vector2f mouseCoords = static_cast<sf::Vector2f>(clickPos);

	bool ballWasClicked = false;
	for (auto& ball : m_jugglingBalls) {
		if (ball.tryClick(mouseCoords)) {
			ballWasClicked = true;
			updateScore(); // Increase score on catch
		}
	}

	if (ballWasClicked) {
		switchClownJuggleTexture();
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
			m_lives--;
			m_livesText.setString("Lives: " + std::to_string(m_lives));
			switchClownPoseTexture();
			std::cout << "You dropped the ball :(" << std::endl;

			if (m_lives <= 0) {
				// Save circus score
				GameScores::circusScore = m_score;
				GameScores::circusCompleted = true;
				GameScores::updateTotal();

				// Check if both games are done
				if (GameScores::bothGamesCompleted()) {
					m_changeScene = true;
					m_changeSceneTo = SceneType::GAME_OVER;
				}
				else {
					m_changeScene = true;
					m_changeSceneTo = SceneType::CHEST;
				}
			}
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
	m_window->draw(m_theatreBackgroundSprite);
	m_window->draw(m_circusBackgroundSprite);
	m_window->draw(m_clownSprite);
	m_window->draw(m_popcornSprite);
	for (auto& ball : m_jugglingBalls) {
		ball.draw(m_window);
	}
	m_window->draw(m_scoreText);
	m_window->draw(m_livesText);
}