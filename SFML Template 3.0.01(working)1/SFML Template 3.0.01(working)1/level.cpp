#include "Level.h"

static int levelTemplate[Level::Height][Level::Width] =
{
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,2,2,3,2,2,3,2,2,0,2,2,3,2,3,3,2,2,0,0,0,0,0,0,0,0,0,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,2,2,3,2,2,3,2,2,0,2,2,3,2,2,3,2,2,2,3,2,2,3,2,0,0,0,0,2,2,3,3,2,3,2,2,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,3,2,2,3,2,2,2,3,2,2,3,2,2,3,2,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,2,2,2,3,2,2,3,2,2,3,2,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,3,2,2,3,2,2,3,2,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,3,2,2,3,2,2,3,2,0,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,3,2,2,3,2,2,3,2,2,2,2,3,2,2,3,2,2,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};

static int BackgroundTemplate[Level::Height][Level::Width] =
{
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,3,1,1,2,1,1,1,2,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 1,1,2,1,1,2,1,1,4,4,5,4,4,5,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,4,4,5,4,4,5,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

void Level::setupTextures()
{
    platformTex.loadFromFile("ASSETS\\IMAGES\\Platform.png");
    houseWall.loadFromFile("ASSETS\\IMAGES\\brickWall.png");
    houseWindow.loadFromFile("ASSETS\\IMAGES\\brickWallWindow.png");
    roofWindow.loadFromFile("ASSETS\\IMAGES\\RoofWallWindow.png");
    roofWall.loadFromFile("ASSETS\\IMAGES\\RoofWall.png");

    railingTex.loadFromFile("ASSETS\\IMAGES\\Rail.png");
    lampPost.loadFromFile("ASSETS\\IMAGES\\lampPost.png");
    railLampPost.loadFromFile("ASSETS\\IMAGES\\railLampPost.png");
    hallway.loadFromFile("ASSETS\\IMAGES\\hallway.png");
    hallway2.loadFromFile("ASSETS\\IMAGES\\hallway2.png");
    roofVents.loadFromFile("ASSETS\\IMAGES\\roofVents.png");

    load();
}

void Level::load()
{
    //background
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            backgroundData[y][x] = BackgroundTemplate[y][x];

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
            levelData[y][x] = levelTemplate[y][x];

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
                sf::Vector2f pos(x * TileWidth, y * TileHeight);

                sf::Vector2f size(TileWidth, TileHeight);

                if (y < 1)
                {
                    tiles[y][x].setup(roofWindow, pos, size);
                }
                else if (levelData[y - 1][x] == 0)
                {
                    tiles[y][x].setup(roofWindow, pos, size);
                }
                else
                {
                    tiles[y][x].setup(houseWindow, pos, size);
                }
            }
        }
    }
}

void Level::render(sf::RenderWindow& window, bool debug)
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

    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            if (levelData[y][x] != 0)
            {
                tiles[y][x].Render(window, debug);
            }
        }
    }
}

void Level::checkCollisions(Player& player)
{
    sf::Vector2f playerPos = player.collider.getPosition();

    int tileX = static_cast<int>(playerPos.x / TileWidth);
    int tileY = static_cast<int>(playerPos.y / TileHeight);

    tileX = std::clamp(tileX, 0, Width - 1);
    tileY = std::clamp(tileY, 0, Height - 1);

    bool onGround = false;
    sf::FloatRect playerBounds = player.collider.getGlobalBounds();
    float playerBottom = playerBounds.position.y + playerBounds.size.y;

    // Check tiles around player
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

                float distanceToTop = playerBottom - platformTop;

                if (distanceToTop >= -5.0f && distanceToTop <= 5.0f)
                {
                    float playerLeft = playerBounds.position.x;
                    float playerRight = playerBounds.position.x + playerBounds.size.x;
                    float platformLeft = platformBounds.position.x;
                    float platformRight = platformBounds.position.x + platformBounds.size.x;

                    if (playerRight > platformLeft && playerLeft < platformRight)
                    {
                        onGround = true;
                    }
                }

                handleCollision(player, tiles[y][x]);
            }
        }
    }

    player.isGrounded = onGround;
}

void Level::handleCollision(Player& player, Platform& platform)
{
    CollisionType col = platform.isColliding(player.collider);
    sf::FloatRect platformBounds = platform.collider.getGlobalBounds();
    sf::FloatRect playerBounds = player.collider.getGlobalBounds();

    float platformTop = platformBounds.position.y;
    float playerBottom = playerBounds.position.y + playerBounds.size.y;
    float playerTop = playerBounds.position.y;

    switch (col)
    {
    case CollisionType::Top:
        player.isGrounded = true;
        player.verticalVelocity = 0.f;
        player.position.y = platformTop;

        if (player.currentState == player.climb)
            break;

        if (player.currentState == player.wallSlide && !player.isGrounded)
            break;

        break;

    case CollisionType::Left:

        if (player.currentState == player.climb || player.currentState == player.wallSlide)
            break;

        if (player.facing == Direction::RIGHT)
        {
            float platformLeft = platformBounds.position.x;
            float playerWidth = playerBounds.size.x;
            player.position.x = platformLeft - (playerWidth / 2.0f);


            player.speed = 0.f;
            player.horizontalVelocity = 0.f;
            player.slideVelocity = 0.f;

            if (player.currentState == player.falling)
            {
                if (player.headSensor.getGlobalBounds().findIntersection(platformBounds).has_value())
                {
                    player.changeState(player.wallSlide);
                    break;
                }
                else
                {
                    player.position.y = platformTop + playerBounds.size.y;
                    player.changeState(player.climb);
                    break;
                }
            }
        }
        break;

    case CollisionType::Right:

        if (player.currentState == player.climb || player.currentState == player.wallSlide && player.isGrounded)
            break;

        if (player.facing == Direction::LEFT)
        {
            player.speed = 0.f;
            player.horizontalVelocity = 0.f;
            player.slideVelocity = 0.f;

            float platformRight = platformBounds.position.x + platformBounds.size.x;
            float playerWidth = playerBounds.size.x;
            player.position.x = platformRight + (playerWidth / 2.0f);

            if (player.currentState == player.falling)
            {
                if (player.headSensor.getGlobalBounds().findIntersection(platformBounds).has_value())
                {
                    player.changeState(player.wallSlide);
                    break;
                }
                else
                {
                    player.position.y = platformTop + playerBounds.size.y;
                    player.changeState(player.climb);
                    break;
                }
            }
        }
        break;

    case CollisionType::Bottom:
        if (player.currentState == player.wallSlide && !player.isGrounded)
            break;

        if (player.isGrounded)
        {
            player.crouching = true;
            player.changeState(player.idleToCrouch);
        }
        else
        {
            player.verticalVelocity = 0;
            player.verticalVelocity += player.gravity;
            player.changeState(player.falling);
        }
        break;

    default:
        break;
    }
}