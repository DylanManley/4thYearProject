#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.h"
#include "level.h"
#include "Enemy.h"

enum class GameState
{
	MENU,
	GAMEPLAY,
	END,
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
	void nextLevel();
	
	void setupTexts();
	void setupSprites();
	void setupAudio();
	
	sf::RenderWindow m_window;    
	sf::Font m_jerseyFont;    
	
	sf::Text m_DELETEwelcomeMessage{ m_jerseyFont };       
	sf::Texture m_DELETElogoTexture;      
	sf::Sprite m_DELETElogoSprite{ m_DELETElogoTexture };      
	sf::Texture backgroundTex;
	sf::Sprite background{ backgroundTex };
	
	sf::SoundBuffer m_DELETEsoundBuffer;     
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer };     
	bool m_DELETEexitGame;    

	Player player;
	Level level;
	std::vector<Enemy> enemies;
	std::vector<sf::Vector2f>getEnemySpawns(int level);

	GameState gameState = GameState::MENU;

	sf::Texture titleScreenTex;
	sf::Sprite titleScreen{ titleScreenTex };
	sf::Texture endScreenTex;
	sf::Sprite endScreen{ endScreenTex };
	sf::Texture titleTex;
	sf::Sprite title{ titleTex };
	sf::Texture titleOptionsTex;
	sf::Sprite titleOptions{ titleOptionsTex };
	sf::View camera;

	int levelNum = 1;

	float uiPadding = 10.f;
	sf::Vector2u winSize = m_window.getSize();

	float mapX = uiPadding / winSize.x;
	float mapY = 0.75f + (uiPadding / winSize.y);
	float mapWidth = 0.25f - (2 * uiPadding / winSize.x);
	float mapHeight = 0.25f - (2 * uiPadding / winSize.y);

	sf::View miniMap;

};

#pragma warning( pop ) 
#endif  

