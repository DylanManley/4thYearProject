#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Player.h"

class Level
{
public:
    static const int Width = 50;
    static const int Height = 20;

    static const int TileWidth = 512;
    static const int TileHeight = 255;

    void setupTextures();
    void load();
    void render(sf::RenderWindow& window, bool debug);
    void checkCollisions(Player& player);
    void handleCollision(Player& player, Platform& platform);

private:
    Platform tiles[Height][Width];
    int levelData[Height][Width];

    std::optional<sf::Sprite> backgroundSprites[Height][Width];
    int backgroundData[Height][Width];

    sf::Texture platformTex;

    //background details
    sf::Texture railingTex;
    sf::Texture hallway;
    sf::Texture hallway2;
    sf::Texture lampPost;
    sf::Texture railLampPost;
};
