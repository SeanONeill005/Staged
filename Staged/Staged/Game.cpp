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
	m_window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
		"Staged",
		sf::Style::Titlebar | sf::Style::Close
	);

	m_window->setKeyRepeatEnabled(false);
	//m_window->setMouseCursorVisible(false);

	sf::View view(RESOLUTION / 2.f, RESOLUTION);
	m_window->setView(view);
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

	// Now load them all in parallel
	if (!texManager.loadQueuedTextures()) {
		std::cerr << "Failed to load some textures!" << std::endl;
	}
}
