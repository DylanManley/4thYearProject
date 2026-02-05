#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Player.h"

class Level
{
public:
    static const int Width = 50;
    static const int Height = 20;

    static const int TileWidth = 256;
    static const int TileHeight = 255;

    void load(sf::Texture& platformTexture);
    void render(sf::RenderWindow& window, bool debug);
    void checkCollisions(Player& player);
    void handleCollision(Player& player, Platform& platform);

private:
    Platform m_tiles[Height][Width];
    int m_levelData[Height][Width];
};
