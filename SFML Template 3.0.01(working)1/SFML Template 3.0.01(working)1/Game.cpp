/// <summary>
/// author Dylan Manley
/// you need to change the above line or lose marks
/// </summary>


#include "Game.h"
#include <iostream>
#include <queue> 



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the texts
/// load and setup the images
/// load and setup the sounds
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{1280, 720}, 32U }, "Knuckle Duster" },
	m_DELETEexitGame{false} //when true game will exit
{
	//setupTexts(); // load font 
	setupSprites(); // load texture
	setupAudio(); // load sounds
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// </summary>
void Game::processEvents()
{
	
	while (const std::optional newEvent = m_window.pollEvent())
	{
		if (newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_DELETEexitGame = true;
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed *newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_DELETEexitGame = true; 
	}

}

/// <summary>
/// Check if any keys are currently pressed
/// </summary>
void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_DELETEexitGame = true; 
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	checkKeyboardState();
	if (m_DELETEexitGame)
	{
		m_window.close();
	}

	switch (gameState)
	{
	case GameState::MENU:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		{
			gameState = GameState::GAMEPLAY;
			setupSprites();
		}
		break;
	case GameState::GAMEPLAY:
		level.checkCollisions(player);
		player.update();

		for (auto& enemy : enemies)
		{
			level.checkCollisions(enemy);
			enemy.update(player);

			if (player.hitSensor.getGlobalBounds().findIntersection(enemy.collider.getGlobalBounds()))
				if (player.attacking)
					enemy.takeDamage(20);

			if (enemy.hitSensor.getGlobalBounds().findIntersection(player.collider.getGlobalBounds()))
				if (enemy.attacking && !enemy.isDead)
					player.takeDamage(5);
		}

		if (player.isDead)
		{
			levelNum = 1;
			gameState = GameState::MENU;
		}

		if (level.levelFinished)
		{
			nextLevel();
		}

		camera.setCenter({ player.body.getPosition().x, player.body.getPosition().y - 200 });
		miniMap.setCenter({ player.body.getPosition() });
		background.setPosition(sf::Vector2f{ player.body.getPosition().x, player.body.getPosition().y + 150 });
		break;
	default:
		break;
	}

	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	sf::RectangleShape border(sf::Vector2f(sf::Vector2f({ winSize.x * 0.25f - 2 * uiPadding, winSize.y * 0.25f - 2 * uiPadding })));
	border.setPosition(sf::Vector2f{ uiPadding, winSize.y * 0.75f + uiPadding });
	border.setFillColor(sf::Color::Black);
	border.setOutlineColor(sf::Color::White);
	border.setOutlineThickness(2.f);

	switch (gameState)
	{
	case GameState::MENU:
		m_window.setView(m_window.getDefaultView());
		m_window.draw(titleScreen);
		m_window.draw(titleOptions);
		m_window.draw(title);
		break;
	case GameState::GAMEPLAY:
		m_window.setView(camera);
		m_window.draw(background);
		level.render(m_window, false);

		for (auto& enemy : enemies)
		{
			enemy.Render(m_window, false);
		}

		player.Render(m_window, false);

		//UI
		m_window.setView(m_window.getDefaultView());
		m_window.draw(border);

		//minimap
		m_window.setView(miniMap);

		level.render(m_window, true);

		for (auto& enemy : enemies)
		{
			enemy.Render(m_window, true);
		}

		player.Render(m_window, true);

		break;
	default:
		break;
	}
	

	m_window.display();
}

void Game::nextLevel()
{
	levelNum++;
	player.position = sf::Vector2f{ 800.f, 1530.f };
	player.health = 100;
	setupSprites();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupTexts()
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

std::vector<sf::Vector2f> Game::getEnemySpawns(int level)
{
	switch (level)
	{
	case 1:
		return { {3950.f, 1530.f}, {6000.f, 765.f}, { 15491.f, 2040.f } };
	case 2: 
		return { {6636.f, 1530.f}, {8878.f, 2040.f}, {15433.f, 1912.f}, {16567.3, 2167} };
	default: return {};
	}
	return std::vector<sf::Vector2f>();
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprites()
{
	if (!titleScreenTex.loadFromFile(("ASSETS\\IMAGES\\TitleScreen.png")))
	{
		std::cout << "error loading title screen" << std::endl;
	}
	titleScreen.setTexture(titleScreenTex, true);

	if (!titleTex.loadFromFile(("ASSETS\\IMAGES\\Title.png")))
	{
		std::cout << "error loading title" << std::endl;
	}
	title.setTexture(titleTex, true);

	if (!titleOptionsTex.loadFromFile(("ASSETS\\IMAGES\\TitleOptions.png")))
	{
		std::cout << "error loading title" << std::endl;
	}
	titleOptions.setTexture(titleOptionsTex, true);
	titleOptions.setScale(sf::Vector2f{ 0.5,0.5 });
	titleOptions.setPosition(sf::Vector2f{ 70, 500 });

	if (!backgroundTex.loadFromFile(("ASSETS\\IMAGES\\temp_background.png")))
	{
		std::cout << "still wrong" << std::endl;
	}
	background.setTexture(backgroundTex, true);
	background.setPosition(sf::Vector2f{ 0, -200 });
	background.setOrigin(sf::Vector2f{ 640, 853 });
	background.setScale(sf::Vector2f{ 1.5,1.5 });

	level.setupTextures(levelNum);
	camera.setSize({ 1280.f, 720.f });
	miniMap.setSize({ 12800, 7200 });

	player.setUp({ 800.f, 1530.f });

	enemies.clear();
	auto spawns = getEnemySpawns(levelNum);
	enemies.reserve(spawns.size()); // prevents reallocation
	for (auto& spawnPos : spawns)
	{
		enemies.emplace_back();
		enemies.back().setUp(spawnPos);
	}

	miniMap.setViewport(sf::FloatRect({ mapX, mapY }, { mapWidth, mapHeight }));
}


/// <summary>
/// load sound file and assign buffers
/// </summary>
void Game::setupAudio()
{

}


