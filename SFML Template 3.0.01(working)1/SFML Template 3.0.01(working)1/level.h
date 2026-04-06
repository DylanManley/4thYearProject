#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Entity.h"

class Level
{
public:
    static const int Width = 50;
    static const int Height = 20;

    static const int TileWidth = 512;
    static const int TileHeight = 255;

    void setupTextures(int levelNum);
    void load(int levelNum);
    void render(sf::RenderWindow& window, bool mapView);
    void checkCollisions(Entity& entity);
    void handleCollision(Entity& entity, Platform& platform);

    bool levelFinished;

private:
    bool loadFromFile(const std::string& filename, int data[Height][Width]);
    Platform tiles[Height][Width];
    int levelData[Height][Width];

    std::optional<sf::Sprite> backgroundSprites[Height][Width];
    int backgroundData[Height][Width];

    sf::Texture platformTex;
    sf::Texture houseWall;
    sf::Texture houseWindow;
    sf::Texture houseWindow2;
    sf::Texture roofWall;
    sf::Texture roofWindow;
    sf::Texture roofWindow2;
    sf::Texture halfRoof;
    sf::Texture crawlSpace;
    sf::Texture exitDoor;

    //background details
    sf::Texture railingTex;
    sf::Texture hallway;
    sf::Texture hallway2;
    sf::Texture lampPost;
    sf::Texture railLampPost;
    sf::Texture roofVents;
    sf::Texture vent;
};
