#include "WesternScene.h"

WesternScene::WesternScene()
	: m_theatreBackgroundSprite(TextureManager::getInstance().get(Textures::Backgrounds::Theatre))
	, m_westernBackgroundSprite(TextureManager::getInstance().get(Textures::Backgrounds::Western))
	, playerSprite(TextureManager::getInstance().get(Textures::Cowboy::Pose1))
	, cactusSprite1(TextureManager::getInstance().get(Textures::Props::Cactus))
	, cactusSprite2(TextureManager::getInstance().get(Textures::Props::Cactus))
	, targetSprite(TextureManager::getInstance().get(Textures::Props::Target))
	, hitMarkerSprite(TextureManager::getInstance().get(Textures::UI::HitMarker))
{
	setupTexts();
	setupSprites();
	gameTimer.restart();
	setRandomPosition();
}

WesternScene::~WesternScene()
{
}

void WesternScene::processEvents()
{
	while (const std::optional e = m_window->pollEvent())
	{
		if (e->is<sf::Event::Closed>()) { m_window->close(); }
		else if (e->is<sf::Event::KeyPressed>()) { processKeys(e); }
		else if (e->is<sf::Event::MouseButtonPressed>()) { processClick(e); }
	}
	if (gameCompleted)
	{
		gameCompleted = false;
		SceneManager::getInstance()->setScene(m_setSceneTo);
	}
}

void WesternScene::setCowboyDirection(bool facingLeft)
{
	if (facingLeft != m_cowboyFacingLeft) {
		// Flip the sprite horizontally
		sf::Vector2f currentScale = playerSprite.getScale();
		playerSprite.setScale({ -currentScale.x, currentScale.y });
		m_cowboyFacingLeft = facingLeft;
	}
}

void WesternScene::processClick(const std::optional<sf::Event> t_event)
{
	const sf::Event::MouseButtonPressed* newMousePress = t_event->getIf<sf::Event::MouseButtonPressed>();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2f mouseCoords = getMousePosition();

		if (targetSprite.getGlobalBounds().contains(mouseCoords))
		{
			score += 3;
			scoreText.setString("Score: " + std::to_string(score));

			// Determine which side of the screen was clicked
			bool clickedOnLeft = mouseCoords.x < (WINDOW_WIDTH / 2.f);
			setCowboyDirection(clickedOnLeft);

			// Switch to shoot animation
			playerSprite.setTexture(TextureManager::getInstance().get(Textures::Cowboy::Shoot));
			isAnimating = true;
			animationTimer.restart();

			// Show hit marker at target position
			showHitMarker(targetSprite.getPosition());

			setRandomPosition();
		}
		else
		{
			// Determine which side of the screen was clicked
			bool clickedOnLeft = mouseCoords.x < (WINDOW_WIDTH / 2.f);
			setCowboyDirection(clickedOnLeft);

			// Clicked but missed the target - show miss animation
			playerSprite.setTexture(TextureManager::getInstance().get(Textures::Cowboy::Pose2));
			isAnimating = true;
			animationTimer.restart();
		}
	}
}

void WesternScene::processKeys(const std::optional<sf::Event> t_event)
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

float WesternScene::getTargetSpeed()
{
	float gameTime = gameTimer.getElapsedTime().asSeconds();
	float speedUpDuration = 60.0f;
	float progress = std::min(gameTime / speedUpDuration, 1.0f);
	return initialTargetTime - (progress * (initialTargetTime - minimumTargetTime));
}

void WesternScene::showHitMarker(sf::Vector2f position)
{
	hitMarkerSprite.setPosition(position);
	showingHitMarker = true;
	animationTimer.restart();
}

void WesternScene::update(sf::Time t_dT)
{
	// Handle animation timer
	if (isAnimating && animationTimer.getElapsedTime() >= animationDuration) {
		playerSprite.setTexture(TextureManager::getInstance().get(Textures::Cowboy::Pose1));
		isAnimating = false;
	}

	// Handle hit marker display
	if (showingHitMarker && animationTimer.getElapsedTime() >= animationDuration) {
		showingHitMarker = false;
	}

	// Update target speed based on game time
	maxTime = sf::seconds(getTargetSpeed());

	elapsedTime += t_dT;
	if (elapsedTime > maxTime) {
		// Target missed!
		missedTargets++;
		missedText.setString("Missed: " + std::to_string(missedTargets) + "/" + std::to_string(maxMissedTargets));

		// Switch to miss animation
		playerSprite.setTexture(TextureManager::getInstance().get(Textures::Cowboy::Pose2));
		isAnimating = true;
		animationTimer.restart();

		if (missedTargets >= maxMissedTargets) {
			GameScores::westernScore = score;
			GameScores::westernCompleted = true;
			GameScores::updateTotal();

			if (GameScores::bothGamesCompleted()) {
				gameCompleted = true;
				m_setSceneTo = SceneType::GAME_OVER;
			}
			else {
				gameCompleted = true;
				m_setSceneTo = SceneType::CHEST;
			}
		}
		else {
			setRandomPosition();
		}
	}

	// Scale the target over time
	float scaleProgress = 1 - (elapsedTime / maxTime);
	currentScale = scaleProgress * 0.5f;
	if (currentScale < 0.1f) currentScale = 0.1f;
	targetSprite.setScale({ currentScale, currentScale });
}

void WesternScene::render()
{
	m_window->clear(sf::Color::White);
	m_window->draw(m_theatreBackgroundSprite);
	m_window->draw(m_westernBackgroundSprite);
	m_window->draw(playerSprite);
	m_window->draw(cactusSprite1);
	m_window->draw(cactusSprite2);
	m_window->draw(targetSprite);

	// Draw hit marker if showing
	if (showingHitMarker) {
		m_window->draw(hitMarkerSprite);
	}

	m_window->draw(scoreText);
	m_window->draw(missedText);
}

void WesternScene::setupTexts()
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

void WesternScene::setupSprites()
{
	// Set up western background
	sf::FloatRect westernBounds = m_westernBackgroundSprite.getLocalBounds();
	m_westernBackgroundSprite.setOrigin({ westernBounds.size.x / 2.f, westernBounds.size.y / 2.f });
	m_westernBackgroundSprite.setPosition({ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT * 0.4f });

	// Set up player sprite
	sf::FloatRect playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin({ playerBounds.size.x / 2.f, playerBounds.size.y / 2.f });
	playerSprite.setScale(sf::Vector2f{ .2f, .2f });
	playerSprite.setPosition(sf::Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.6f });

	// Set up cactus 1 (left side)
	sf::FloatRect cactus1Bounds = cactusSprite1.getLocalBounds();
	cactusSprite1.setOrigin({ cactus1Bounds.size.x / 2.f, cactus1Bounds.size.y });
	cactusSprite1.setScale({ 0.4f, 0.4f });
	cactusSprite1.setPosition({ 400.f, WINDOW_HEIGHT - 50.f });

	// Set up cactus 2 (right side)
	sf::FloatRect cactus2Bounds = cactusSprite2.getLocalBounds();
	cactusSprite2.setOrigin({ cactus2Bounds.size.x / 2.f, cactus2Bounds.size.y });
	cactusSprite2.setScale({ 0.5f, 0.5f });
	cactusSprite2.setPosition({ WINDOW_WIDTH - 400.f, WINDOW_HEIGHT - 50.f });

	// Set up target sprite
	sf::FloatRect targetBounds = targetSprite.getLocalBounds();
	targetSprite.setOrigin({ targetBounds.size.x / 2.f, targetBounds.size.y / 2.f });
	targetSprite.setScale({ 0.5f, 0.5f });

	// Set up hit marker sprite
	sf::FloatRect hitMarkerBounds = hitMarkerSprite.getLocalBounds();
	hitMarkerSprite.setOrigin({ hitMarkerBounds.size.x / 2.f, hitMarkerBounds.size.y / 2.f });
	hitMarkerSprite.setScale({ 0.3f, 0.3f });

	scoreText.setCharacterSize(60);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setPosition(sf::Vector2f{ 10.0f, 10.0f });
	scoreText.setString("Score: 0");

	missedText.setCharacterSize(60);
	missedText.setFillColor(sf::Color::Red);
	missedText.setPosition(sf::Vector2f{ 10.0f, 80.0f });
	missedText.setString("Missed: 0/" + std::to_string(maxMissedTargets));
}

void WesternScene::setRandomPosition()
{
	float minX = edgeMargin;
	float maxX = RESOLUTION.x - edgeMargin;
	float minY = edgeMargin;
	float maxY = RESOLUTION.y - edgeMargin;

	float posX = minX + (rand() % static_cast<int>(maxX - minX));
	float posY = minY + (rand() % static_cast<int>(maxY - minY));

	targetSprite.setPosition(sf::Vector2f{ posX, posY });
	currentScale = 0.5f;
	targetSprite.setScale({ currentScale, currentScale });
	elapsedTime = sf::Time::Zero;
}