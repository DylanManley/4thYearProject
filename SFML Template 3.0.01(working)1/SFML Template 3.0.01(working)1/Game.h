/// <summary>
/// author Dylan Manley
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
// ignore this warning
// C:\SFML - 3.0.0\include\SFML\System\Exception.hpp(41, 47) : 
// warning C4275 : non dll - interface class 'std::runtime_error' used as base for dll - interface class 'sf::Exception'

/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the #endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.h"
#include "level.h"
#include "Enemy.h"

enum class GameState
{
	MENU,
	GAMEPLAY,
};


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
	
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_jerseyFont;// font used by message
	
	sf::Text m_DELETEwelcomeMessage{ m_jerseyFont }; // text used for message on screen
	sf::Texture m_DELETElogoTexture;//  texture used for sfml logo
	sf::Sprite m_DELETElogoSprite{ m_DELETElogoTexture }; // sprite used for sfml logo
	sf::Texture backgroundTex;
	sf::Sprite background{ backgroundTex };
	
	sf::SoundBuffer m_DELETEsoundBuffer; // buffer for beep sound
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer }; // sound object to play
	bool m_DELETEexitGame; // control exiting game

	Player player;
	Level level;
	Enemy enemy1;
	GameState gameState = GameState::MENU;

	sf::Texture titleScreenTex;
	sf::Sprite titleScreen{ titleScreenTex };
	sf::Texture titleTex;
	sf::Sprite title{ titleTex };
	sf::Texture titleOptionsTex;
	sf::Sprite titleOptions{ titleOptionsTex };
	sf::View camera;


	float uiPadding = 10.f;
	sf::Vector2u winSize = m_window.getSize();

	float mapX = uiPadding / winSize.x;
	float mapY = 0.75f + (uiPadding / winSize.y);
	float mapWidth = 0.25f - (2 * uiPadding / winSize.x);
	float mapHeight = 0.25f - (2 * uiPadding / winSize.y);

	sf::View miniMap;

};

#pragma warning( pop ) 
#endif // !GAME_HPP

