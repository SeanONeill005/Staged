#include "GameOverScene.h"

GameOverScene::GameOverScene()
	: m_theatreBackgroundSprite(TextureManager::getInstance().get(Textures::Backgrounds::Theatre))
{
	setupSprites();
	setupTexts();
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::setupSprites()
{
	// Background is already set up in initializer list
}

void GameOverScene::setupTexts()
{
	// Game Over title
	m_gameOverText.setString("GAME OVER");
	m_gameOverText.setCharacterSize(120);
	m_gameOverText.setFillColor(sf::Color::Red);
	sf::FloatRect gameOverBounds = m_gameOverText.getLocalBounds();
	m_gameOverText.setOrigin({ gameOverBounds.size.x / 2.f, gameOverBounds.size.y / 2.f });
	m_gameOverText.setPosition({ WINDOW_WIDTH / 2.f, 150.f });

	// Your scores section
	m_westernScoreText.setString("Western Score: " + std::to_string(GameScores::westernScore));
	m_westernScoreText.setCharacterSize(70);
	m_westernScoreText.setFillColor(sf::Color::Black);
	m_westernScoreText.setPosition({ 200.f, 350.f });

	m_circusScoreText.setString("Circus Score: " + std::to_string(GameScores::circusScore));
	m_circusScoreText.setCharacterSize(70);
	m_circusScoreText.setFillColor(sf::Color::Black);
	m_circusScoreText.setPosition({ 200.f, 450.f });

	m_totalScoreText.setString("Total Score: " + std::to_string(GameScores::totalScore));
	m_totalScoreText.setCharacterSize(80);
	m_totalScoreText.setFillColor(sf::Color::Blue);
	m_totalScoreText.setPosition({ 200.f, 550.f });

	// Name entry section
	m_namePromptText.setString("Enter Your Name (3 letters):");
	m_namePromptText.setCharacterSize(60);
	m_namePromptText.setFillColor(sf::Color::Black);
	m_namePromptText.setPosition({ 200.f, 680.f });

	m_nameInputText.setString(m_playerName);
	m_nameInputText.setCharacterSize(100);
	m_nameInputText.setFillColor(sf::Color::Green);
	m_nameInputText.setPosition({ 300.f, 760.f });

	// Best scores section with names
	auto& scoreManager = ScoreManager::getInstance();
	auto scores = scoreManager.loadScores();

	// Find best western
	std::string bestWesternName = "---";
	int bestWestern = 0;
	if (!scores.empty()) {
		auto maxWestern = std::max_element(scores.begin(), scores.end(),
			[](const ScoreEntry& a, const ScoreEntry& b) {
				return a.westernScore < b.westernScore;
			});
		bestWestern = maxWestern->westernScore;
		bestWesternName = maxWestern->name;
	}

	// Find best circus
	std::string bestCircusName = "---";
	int bestCircus = 0;
	if (!scores.empty()) {
		auto maxCircus = std::max_element(scores.begin(), scores.end(),
			[](const ScoreEntry& a, const ScoreEntry& b) {
				return a.circusScore < b.circusScore;
			});
		bestCircus = maxCircus->circusScore;
		bestCircusName = maxCircus->name;
	}

	// Find best total
	std::string bestTotalName = "---";
	int bestTotal = 0;
	if (!scores.empty()) {
		auto maxTotal = std::max_element(scores.begin(), scores.end(),
			[](const ScoreEntry& a, const ScoreEntry& b) {
				return a.totalScore < b.totalScore;
			});
		bestTotal = maxTotal->totalScore;
		bestTotalName = maxTotal->name;
	}

	m_bestWesternText.setString("Best Western: " + std::to_string(bestWestern) + " (" + bestWesternName + ")");
	m_bestWesternText.setCharacterSize(50);
	m_bestWesternText.setFillColor(sf::Color(100, 100, 100));
	m_bestWesternText.setPosition({ 1050.f, 350.f });

	m_bestCircusText.setString("Best Circus: " + std::to_string(bestCircus) + " (" + bestCircusName + ")");
	m_bestCircusText.setCharacterSize(50);
	m_bestCircusText.setFillColor(sf::Color(100, 100, 100));
	m_bestCircusText.setPosition({ 1050.f, 420.f });

	m_bestTotalText.setString("Best Total: " + std::to_string(bestTotal) + " (" + bestTotalName + ")");
	m_bestTotalText.setCharacterSize(50);
	m_bestTotalText.setFillColor(sf::Color(100, 100, 100));
	m_bestTotalText.setPosition({ 1050.f, 490.f });

	// Instructions
	m_pressKeyText.setString("Use UP/DOWN arrows to change letter\nLEFT/RIGHT to move cursor\nPress ENTER to save");
	m_pressKeyText.setCharacterSize(40);
	m_pressKeyText.setFillColor(sf::Color::White);
	m_pressKeyText.setPosition({ 200.f, 900.f });
}

void GameOverScene::updateNameDisplay()
{
	m_nameInputText.setString(m_playerName);
}

void GameOverScene::saveScoreAndReturn()
{
	if (!m_scoreSaved) {
		// Save the score with the player's name
		ScoreManager::getInstance().saveScore(
			m_playerName,
			GameScores::westernScore,
			GameScores::circusScore
		);
		m_scoreSaved = true;
		std::cout << "Score saved for " << m_playerName << std::endl;
	}
	m_returnToMenu = true;
}

void GameOverScene::processEvents()
{
	while (const std::optional e = m_window->pollEvent())
	{
		if (e->is<sf::Event::Closed>()) { m_window->close(); }
		else if (e->is<sf::Event::KeyPressed>()) { processKeys(e); }
		else if (e->is<sf::Event::MouseButtonPressed>()) { processClick(e); }
	}

	if (m_returnToMenu) {
		// Reset scores for a new game
		GameScores::resetScores();
		SceneManager::getInstance()->setScene(SceneType::MAIN_MENU);
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
	else if (sf::Keyboard::Key::Enter == newKeypress->code)
	{
		saveScoreAndReturn();
	}
	else if (sf::Keyboard::Key::Left == newKeypress->code)
	{
		// Move cursor left
		m_currentLetterIndex = (m_currentLetterIndex - 1 + 3) % 3;
		updateNameDisplay();
	}
	else if (sf::Keyboard::Key::Right == newKeypress->code)
	{
		// Move cursor right
		m_currentLetterIndex = (m_currentLetterIndex + 1) % 3;
		updateNameDisplay();
	}
	else if (sf::Keyboard::Key::Down == newKeypress->code)
	{
		// Increment current letter (A->B->C...->Z)
		char currentChar = m_playerName[m_currentLetterIndex];
		if (currentChar == 'Z') {
			m_playerName[m_currentLetterIndex] = 'A';
		}
		else {
			m_playerName[m_currentLetterIndex] = currentChar + 1;
		}
		updateNameDisplay();
	}
	else if (sf::Keyboard::Key::Up == newKeypress->code)
	{
		// Decrement current letter (Z->Y->X...->A)
		char currentChar = m_playerName[m_currentLetterIndex];
		if (currentChar == 'A') {
			m_playerName[m_currentLetterIndex] = 'Z';
		}
		else {
			m_playerName[m_currentLetterIndex] = currentChar - 1;
		}
		updateNameDisplay();
	}
}

void GameOverScene::update(sf::Time t_dT)
{
}

void GameOverScene::render()
{
	m_window->clear(sf::Color::White);
	m_window->draw(m_theatreBackgroundSprite);
	m_window->draw(m_gameOverText);
	m_window->draw(m_westernScoreText);
	m_window->draw(m_circusScoreText);
	m_window->draw(m_totalScoreText);
	m_window->draw(m_namePromptText);
	m_window->draw(m_nameInputText);
	m_window->draw(m_bestWesternText);
	m_window->draw(m_bestCircusText);
	m_window->draw(m_bestTotalText);
	m_window->draw(m_pressKeyText);
	m_window->display();
}