#include "Level.h"
#include <iostream>
#include <fstream>
#include <sstream>

//static int levelTemplate[Level::Height][Level::Width] =
//{
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,2,2,3,2,2,3,2,2,0,2,2,3,2,3,3,2,2,4,0,0,0,0,0,0,0,0,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,2,2,3,2,2,3,2,2,0,2,2,3,2,2,3,2,2,2,3,2,2,3,2,0,0,0,0,2,2,3,3,2,3,2,2,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,3,2,2,3,2,2,2,3,2,2,3,2,2,3,2,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
//    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,2,2,2,3,2,2,3,2,2,3,2,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,2,2,3,2,2,3,2,2,3,2,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,3,2,2,3,2,2,3,2,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,3,2,2,3,2,2,3,2,2,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
//};
//
//static int BackgroundTemplate[Level::Height][Level::Width] =
//{
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,3,1,1,2,1,1,1,2,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 1,1,2,1,1,2,1,1,4,4,5,4,4,5,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,7,7,7,4,4,5,4,4,5,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
//    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
//    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
//};

bool Level::loadFromFile(const std::string& filename, int data[Height][Width])
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to open: " << filename << "\n";
        return false;
    }

    std::string line;
    int y = 0;

    while (std::getline(file, line) && y < Height)
    {
        std::stringstream ss(line);
        int x = 0;

        while (ss >> data[y][x] && x < Width)
        {
            x++;
        }

        y++;
    }

    return true;
}

void Level::setupTextures()
{
    platformTex.loadFromFile("ASSETS\\IMAGES\\Platform.png");
    houseWall.loadFromFile("ASSETS\\IMAGES\\brickWall.png");
    houseWindow.loadFromFile("ASSETS\\IMAGES\\brickWallWindow.png");
    houseWindow2.loadFromFile("ASSETS\\IMAGES\\brickWallWindow2.png");
    roofWindow.loadFromFile("ASSETS\\IMAGES\\RoofWallWindow.png");
    roofWindow2.loadFromFile("ASSETS\\IMAGES\\RoofWallWindow2.png");
    roofWall.loadFromFile("ASSETS\\IMAGES\\RoofWall.png");
    halfRoof.loadFromFile("ASSETS\\IMAGES\\RoofWallSlab.png");
    crawlSpace.loadFromFile("ASSETS\\IMAGES\\crawlspace.png");


    //backgrounds
    railingTex.loadFromFile("ASSETS\\IMAGES\\Rail.png");
    lampPost.loadFromFile("ASSETS\\IMAGES\\lampPost.png");
    railLampPost.loadFromFile("ASSETS\\IMAGES\\railLampPost.png");
    hallway.loadFromFile("ASSETS\\IMAGES\\hallway.png");
    hallway2.loadFromFile("ASSETS\\IMAGES\\hallway2.png");
    roofVents.loadFromFile("ASSETS\\IMAGES\\roofVents.png");
    vent.loadFromFile("ASSETS\\IMAGES\\vent.jpg");

    load();
}

void Level::load()
{
    //load Level and background files
    loadFromFile("ASSETS\\LEVELS\\level1.txt", levelData);
    loadFromFile("ASSETS\\LEVELS\\background1.txt", backgroundData);

    //background
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            //backgroundData[y][x] = BackgroundTemplate[y][x];

            if (backgroundData[y][x] == 1)
            {
                sf::Sprite sprite(railingTex);
                sprite.setPosition(sf::Vector2f{ static_cast<float>(x * TileWidth), static_cast<float>(y * TileHeight) });
                backgroundSprites[y][x] = std::move(sprite);
            }
            else if (backgroundData[y][x] == 2)
            {
                sf::Sprite sprite(railLampPost);
                sprite.setPosition(sf::Vector2f{ static_cast<float>(x * TileWidth), static_cast<float>(y * TileHeight) });
                backgroundSprites[y][x] = std::move(sprite);
            }
            else if (backgroundData[y][x] == 3)
            {
                sf::Sprite sprite(lampPost);
                sprite.setPosition(sf::Vector2f{ static_cast<float>(x * TileWidth), static_cast<float>(y * TileHeight) });
                backgroundSprites[y][x] = std::move(sprite);
            }
            else if (backgroundData[y][x] == 4)
            {
                sf::Sprite sprite(hallway);
                sprite.setPosition(sf::Vector2f{ static_cast<float>(x * TileWidth), static_cast<float>(y * TileHeight) });
                backgroundSprites[y][x] = std::move(sprite);
            }
            else if (backgroundData[y][x] == 5)
            {
                sf::Sprite sprite(hallway2);
                sprite.setPosition(sf::Vector2f{ static_cast<float>(x * TileWidth), static_cast<float>(y * TileHeight) });
                backgroundSprites[y][x] = std::move(sprite);
            }
            else if (backgroundData[y][x] == 6)
            {
                sf::Sprite sprite(roofVents);
                sprite.setPosition(sf::Vector2f{ static_cast<float>(x * TileWidth), static_cast<float>(y * TileHeight) });
                backgroundSprites[y][x] = std::move(sprite);
            }
            else if (backgroundData[y][x] == 7)
            {
                sf::Sprite sprite(vent);
                sprite.setPosition(sf::Vector2f{ static_cast<float>(x * TileWidth), static_cast<float>(y * TileHeight) });
                backgroundSprites[y][x] = std::move(sprite);
            }
            else
            {
                backgroundSprites[y][x].reset();
            }
        }
    }

    //playable area
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            //levelData[y][x] = levelTemplate[y][x];

            if (levelData[y][x] == 1)
            {
                sf::Vector2f pos(x * TileWidth, y * TileHeight);

                sf::Vector2f size(TileWidth, TileHeight);

                tiles[y][x].setup(platformTex, pos, size);
            }
            else if (levelData[y][x] == 2)
            {
                sf::Vector2f pos(x * TileWidth, y * TileHeight);

                sf::Vector2f size(TileWidth, TileHeight);

                if (y < 1)
                {
                    tiles[y][x].setup(roofWall, pos, size);
                }
                else if (levelData[y-1][x] == 0)
                {
                    tiles[y][x].setup(roofWall, pos, size);
                }
                else
                {
                    tiles[y][x].setup(houseWall, pos, size);
                }
            }
            else if (levelData[y][x] == 3)
            {
                int lit = rand() % 2;

                sf::Vector2f pos(x * TileWidth, y * TileHeight);

                sf::Vector2f size(TileWidth, TileHeight);

                if (y < 1)
                {
                    if (lit == 1)
                        tiles[y][x].setup(roofWindow, pos, size);
                    else
                        tiles[y][x].setup(roofWindow2, pos, size);

                }
                else if (levelData[y - 1][x] == 0)
                {
                        if (lit == 1)
                            tiles[y][x].setup(roofWindow, pos, size);
                        else
                            tiles[y][x].setup(roofWindow2, pos, size);
                }
                else
                {
                        if (lit == 1)
                            tiles[y][x].setup(houseWindow, pos, size);
                        else
                            tiles[y][x].setup(houseWindow2, pos, size);
                }
            }
            else if (levelData[y][x] == 4)
            {
                sf::Vector2f pos(x* TileWidth, y* TileHeight + (TileHeight/2));

                sf::Vector2f size(TileWidth, TileHeight);

                tiles[y][x].setup(halfRoof, pos, size);
            }
            else if (levelData[y][x] == 5)
            {
                sf::Vector2f pos(x * TileWidth, y * TileHeight);

                sf::Vector2f size(TileWidth, TileHeight);

                tiles[y][x].setup(crawlSpace, pos, size);
            }
        }
    }
}

void Level::render(sf::RenderWindow& window, bool mapView)
{
    if (!mapView)
    {
        for (int y = 0; y < Height; y++)
        {
            for (int x = 0; x < Width; x++)
            {
                if (backgroundSprites[y][x])
                {
                    window.draw(*backgroundSprites[y][x]);
                }
            }
        }
    }

    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            if (levelData[y][x] != 0)
            {
                tiles[y][x].Render(window, mapView);
            }
        }
    }
}

void Level::checkCollisions(Entity& entity)
{
    sf::Vector2f entityPos = entity.collider.getPosition();

    int tileX = static_cast<int>(entityPos.x / TileWidth);
    int tileY = static_cast<int>(entityPos.y / TileHeight);

    tileX = std::clamp(tileX, 0, Width - 1);
    tileY = std::clamp(tileY, 0, Height - 1);

    bool onGround = false;
    sf::FloatRect entityBounds = entity.collider.getGlobalBounds();
    float entityBottom = entityBounds.position.y + entityBounds.size.y;

    // Check tiles around entity
    for (int y = tileY - 1; y <= tileY + 1; ++y)
    {
        if (y < 0 || y >= Height) continue;
        for (int x = tileX - 1; x <= tileX + 1; ++x)
        {
            if (x < 0 || x >= Width) continue;

            if (levelData[y][x] != 0)
            {
                sf::FloatRect platformBounds = tiles[y][x].collider.getGlobalBounds();
                float platformTop = platformBounds.position.y;

                float distanceToTop = entityBottom - platformTop;

                if (distanceToTop >= -5.0f && distanceToTop <= 5.0f)
                {
                    float entityLeft = entityBounds.position.x;
                    float entityRight = entityBounds.position.x + entityBounds.size.x;
                    float platformLeft = platformBounds.position.x;
                    float platformRight = platformBounds.position.x + platformBounds.size.x;

                    if (entityRight > platformLeft && entityLeft < platformRight)
                    {
                        onGround = true;
                    }
                }

                handleCollision(entity, tiles[y][x]);
            }
        }
    }

    entity.isGrounded = onGround;
}

void Level::handleCollision(Entity& entity, Platform& platform)
{
    CollisionType col = platform.isColliding(entity.collider);
    sf::FloatRect platformBounds = platform.collider.getGlobalBounds();
    sf::FloatRect entityBounds = entity.collider.getGlobalBounds();

    float platformTop = platformBounds.position.y;
    float platformBottom = platformBounds.position.y + platformBounds.size.y;
    float platformRight = platformBounds.position.x + platformBounds.size.x;
    float platformLeft = platformBounds.position.x;

    float entityBottom = entityBounds.position.y + entityBounds.size.y;
    float entityTop = entityBounds.position.y;
    float entityWidth = entityBounds.size.x;
    

    switch (col)
    {
    case CollisionType::Top:
        entity.isGrounded = true;
        entity.verticalVelocity = 0.f;
        entity.position.y = platformTop;

        if (entity.currentState == entity.climb)
            break;

        if (entity.currentState == entity.wallSlide && !entity.isGrounded)
            break;

        break;

    case CollisionType::Left:

        if (entity.currentState == entity.climb || entity.currentState == entity.wallSlide)
            break;

        entity.speed = 0.f;
        entity.horizontalVelocity = 0.f;
        entity.slideVelocity = 0.f;
        entity.position.x = platformLeft - (entityWidth / 2.0f);

        if (entity.facing == Direction::RIGHT)
        {

            if (entity.currentState == entity.falling)
            {

                if (entity.headSensor.getGlobalBounds().findIntersection(platformBounds).has_value())
                {
                    entity.changeState(entity.wallSlide);
                    break;
                }
                else
                {
                    entity.position.y = platformTop + entityBounds.size.y;
                    entity.changeState(entity.climb);
                    break;
                }
            }
        }
        break;

    case CollisionType::Right:

        if (entity.currentState == entity.climb || entity.currentState == entity.wallSlide && entity.isGrounded)
            break;

        
        entity.position.x = platformRight + (entityWidth / 2.0f);

        entity.speed = 0.f;
        entity.horizontalVelocity = 0.f;
        entity.slideVelocity = 0.f;

        if (entity.facing == Direction::LEFT)
        {
            if (entity.currentState == entity.falling)
            {
                if (entity.headSensor.getGlobalBounds().findIntersection(platformBounds).has_value())
                {
                    entity.changeState(entity.wallSlide);
                    break;
                }
                else
                {
                    entity.position.y = platformTop + entityBounds.size.y;
                    entity.changeState(entity.climb);
                    break;
                }
            }
        }
        break;

    case CollisionType::Bottom:
        if (entity.currentState == entity.wallSlide && !entity.isGrounded)
            break;

        if (entity.isGrounded)
        {
            entity.crouching = true;
            entity.changeState(entity.idleToCrouch);
        }
        else
        {
            entity.verticalVelocity = 0;
            entity.verticalVelocity += entity.gravity;
            entity.changeState(entity.falling);
            entity.position.y = platformBottom + entityBounds.size.y;
        }
        break;

    default:
        break;
    }
}