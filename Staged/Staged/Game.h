#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Mask.h"
#include "Scene.h"
#include <vector>
const sf::Color ULTRAMARINE{ 5, 55,242,255 }; // const colour

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void checkKeyboardState();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupTexts();
	void setupSprites();
	void setupAudio();

	void printMaskType();

	void processClick(const std::optional<sf::Event> t_event);
	
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_jerseyFont;// font used by message
	
	sf::Text m_DELETEwelcomeMessage{ m_jerseyFont }; // text used for message on screen
	sf::Texture m_backgroundTexture{ "ASSETS/IMAGES/TheatreBackground.png" };//  texture used for sfml logo
	sf::Sprite m_backgroundSprite{ m_backgroundTexture }; // sprite used for sfml logo
	
	sf::SoundBuffer m_DELETEsoundBuffer; // buffer for beep sound
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer }; // sound object to play
	bool m_DELETEexitGame; // control exiting game

	Mask mask = "Blue";
	Mask maskRed = "Red";
	Scene scene = "Purple";
	std::vector<Mask> maskList = { mask, maskRed};

	Mask clickerMask = "ClickerMask";

};

#pragma warning( pop ) 
#endif // !GAME_HPP

