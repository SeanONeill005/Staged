#include "Game.h"


void Game::run()
{
	init();
	loadTextures();

	GameScores::resetScores();

	auto sceneManager = SceneManager::getInstance();
	sceneManager->setRenderWindow(m_window);

	sceneManager->registerScene<MainMenuScene>(SceneType::MAIN_MENU);
	sceneManager->registerScene<WesternScene>(SceneType::WESTERN);
	sceneManager->registerScene<CircusScene>(SceneType::CIRCUS);
	sceneManager->registerScene<BoatScene>(SceneType::BOAT);
	sceneManager->registerScene<ChestScene>(SceneType::CHEST);
	sceneManager->registerScene<GameOverScene>(SceneType::GAME_OVER);

	sceneManager->setScene(SceneType::MAIN_MENU);

	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	const sf::Time MS_PER_UPDATE = sf::seconds(1 / 60.f);

	while (m_window->isOpen()) {
		sf::Time dT = clock.restart();
		lag += dT;

		sceneManager->processEvents();

		while (lag > MS_PER_UPDATE) {
			sceneManager->update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}

		sceneManager->update(dT);
		sceneManager->render();
	}
}

void Game::init()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	m_window = std::make_shared<sf::RenderWindow>(
		desktop,
		"Staged",
		sf::State::Fullscreen
	);

	m_window->setKeyRepeatEnabled(false);
	//m_window->setMouseCursorVisible(false);

	sf::View view(RESOLUTION / 2.f, RESOLUTION);
	m_window->setView(view);

	setupLetterboxView();
}

void Game::loadTextures()
{
	// Queue all textures first (this is instant)
	auto& texManager = TextureManager::getInstance();

	// Props
	texManager.queueLoadFromAssets(Textures::Props::Ball, "Ball.png");
	texManager.queueLoadFromAssets(Textures::Props::Cactus, "Cactus.png");
	texManager.queueLoadFromAssets(Textures::Props::Chest, "Chest.png");
	texManager.queueLoadFromAssets(Textures::Props::Popcorn, "Popcorn.png");
	texManager.queueLoadFromAssets(Textures::Props::Target, "Target.png");
	texManager.queueLoadFromAssets(Textures::Props::Mannequin, "Mannequin.png");
	texManager.queueLoadFromAssets(Textures::Props::Gun, "Gun.png");

	// Backgrounds
	texManager.queueLoadFromAssets(Textures::Backgrounds::Circus, "Circus_Background.png");
	texManager.queueLoadFromAssets(Textures::Backgrounds::Theatre, "TheatreBackground.png");
	texManager.queueLoadFromAssets(Textures::Backgrounds::Western, "Western_Background.png");

	// Clown
	texManager.queueLoadFromAssets(Textures::Clown::Juggle1, "ClownJuggle1.png");
	texManager.queueLoadFromAssets(Textures::Clown::Juggle2, "ClownJuggle2.png");
	texManager.queueLoadFromAssets(Textures::Clown::Mask, "ClownMask.png");
	texManager.queueLoadFromAssets(Textures::Clown::Pose1, "ClownPose1.png");
	texManager.queueLoadFromAssets(Textures::Clown::Pose2, "ClownPose2.png");

	// Cowboy
	texManager.queueLoadFromAssets(Textures::Cowboy::Mask, "CowboyMask.png");
	texManager.queueLoadFromAssets(Textures::Cowboy::Pose1, "CowboyPose1.png");
	texManager.queueLoadFromAssets(Textures::Cowboy::Pose2, "CowboyPose2.png");
	texManager.queueLoadFromAssets(Textures::Cowboy::Shoot, "CowboyShoot.png");

	// UI
	texManager.queueLoadFromAssets(Textures::UI::PlayButton, "PlayButton.png");
	texManager.queueLoadFromAssets(Textures::UI::QuitButton, "QuitButton.png");
	texManager.queueLoadFromAssets(Textures::UI::HitMarker, "HitMarker.png");

	// Stage elements
	texManager.queueLoadFromAssets(Textures::Stage::LeftCurtain, "left_curtain.png");
	texManager.queueLoadFromAssets(Textures::Stage::RightCurtain, "right_curtain.png");
	texManager.queueLoadFromAssets(Textures::Stage::LeftLight, "left_light.png");
	texManager.queueLoadFromAssets(Textures::Stage::RightLight, "right_light.png");

	// Now load them all in parallel
	if (!texManager.loadQueuedTextures()) {
		std::cerr << "Failed to load some textures!" << std::endl;
	}
}

void Game::setupLetterboxView()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	float windowRatio = static_cast<float>(desktop.size.x) / static_cast<float>(desktop.size.y);
	float gameRatio = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);

	sf::View view;
	view.setSize(RESOLUTION);
	view.setCenter(RESOLUTION / 2.f);

	if (windowRatio < gameRatio) {
		float viewportWidth = windowRatio / gameRatio;
		float xOffset = (1.f - viewportWidth) / 2.f;
		view.setViewport(sf::FloatRect(
			sf::Vector2f(xOffset, 0.f),
			sf::Vector2f(viewportWidth, 1.f))
		);
	}
	else {
		float viewportHeight = gameRatio / windowRatio;
		float yOffset = (1.f - viewportHeight) / 2.f;
		view.setViewport(sf::FloatRect(
			sf::Vector2f(0.f, yOffset),
			sf::Vector2f(1.f, viewportHeight)
		));
	}

	m_window->setView(view);
}
