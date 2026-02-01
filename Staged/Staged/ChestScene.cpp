#include "ChestScene.h"

ChestScene::ChestScene()
	: m_menuBackgroundSprite(TextureManager::getInstance().get(Textures::Backgrounds::Theatre))
	, m_chestSprite(TextureManager::getInstance().get(Textures::Props::Chest))
	, m_mask1Sprite(TextureManager::getInstance().get(Textures::Cowboy::Mask))
	, m_mask2Sprite(TextureManager::getInstance().get(Textures::Clown::Mask))
{
	setupMasks();
}

ChestScene::~ChestScene()
{
}

void ChestScene::setupMasks()
{
	m_masks[0] = &m_mask1Sprite;
	m_masks[1] = &m_mask2Sprite;

	// Set up chest sprite
	sf::FloatRect chestBounds = m_chestSprite.getLocalBounds();
	m_chestSprite.setOrigin({ chestBounds.size.x / 2.f, chestBounds.size.y / 2.f });
	m_chestSprite.setPosition({ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f });

	// Set up mask 1 (Cowboy)
	sf::FloatRect bounds1 = m_mask1Sprite.getLocalBounds();
	m_mask1Sprite.setOrigin({ bounds1.size.x / 2.f, bounds1.size.y / 2.f });
	m_mask1Sprite.setPosition({ 760.f, 740.f });

	// Set up mask 2 (Clown)
	sf::FloatRect bounds2 = m_mask2Sprite.getLocalBounds();
	m_mask2Sprite.setOrigin({ bounds2.size.x / 2.f, bounds2.size.y / 2.f });
	m_mask2Sprite.setPosition({ 1130.f, 740.f });

	// Set up grey overlays (match mask bounds)
	m_greyOverlay1.setSize({ bounds1.size.x, bounds1.size.y});
	m_greyOverlay1.setOrigin({ bounds1.size.x / 2.f, bounds1.size.y / 2.f });
	m_greyOverlay1.setPosition(m_mask1Sprite.getPosition());
	m_greyOverlay1.setFillColor(sf::Color(128, 128, 128, 200));

	m_greyOverlay2.setSize({ bounds2.size.x, bounds2.size.y });
	m_greyOverlay2.setOrigin({ bounds2.size.x / 2.f, bounds2.size.y / 2.f });
	m_greyOverlay2.setPosition(m_mask2Sprite.getPosition());
	m_greyOverlay2.setFillColor(sf::Color(128, 128, 128, 200));
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
	sf::Vector2f mouseCoords = getMousePosition();

	for (size_t i = 0; i < m_masks.size(); ++i) {
		if (m_masks[i] && m_masks[i]->getGlobalBounds().contains(mouseCoords)) {
			switch (i) {
			case 0:
				// Don't allow playing western if already completed
				if (!GameScores::westernCompleted) {
					m_changeScene = true;
					m_changeSceneTo = SceneType::WESTERN;
				}
				break;
			case 1:
				// Don't allow playing circus if already completed
				if (!GameScores::circusCompleted) {
					m_changeScene = true;
					m_changeSceneTo = SceneType::CIRCUS;
				}
				break;
			case 2:
				// third mask
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
	m_window->draw(m_menuBackgroundSprite);
	m_window->draw(m_chestSprite);

	// Draw masks
	for (auto* m : m_masks) {
		if (m) {
			m_window->draw(*m);
		}
	}

	// Draw grey overlays on completed games
	if (GameScores::westernCompleted) {
		m_window->draw(m_greyOverlay1);
	}
	if (GameScores::circusCompleted) {
		m_window->draw(m_greyOverlay2);
	}
}
