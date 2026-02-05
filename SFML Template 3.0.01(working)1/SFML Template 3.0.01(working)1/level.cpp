#include "Level.h"

static int levelTemplate[Level::Height][Level::Width] =
{
    { 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
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
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,3,1,1,2,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 1,1,2,1,1,2,1,1,4,4,5,4,4,5,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
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
    railingTex.loadFromFile("ASSETS\\IMAGES\\Rail.png");
    lampPost.loadFromFile("ASSETS\\IMAGES\\lampPost.png");
    railLampPost.loadFromFile("ASSETS\\IMAGES\\railLampPost.png");
    hallway.loadFromFile("ASSETS\\IMAGES\\hallway.png");
    hallway2.loadFromFile("ASSETS\\IMAGES\\hallway2.png");

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
                sprite.setPosition(sf::Vector2f{static_cast<float>(x * TileWidth), static_cast<float>(y * TileHeight) });
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
            if (levelData[y][x] == 1)
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

    for (int y = tileY - 1; y <= tileY + 1; ++y)
    {
        if (y < 0 || y >= Height) continue;
        for (int x = tileX - 1; x <= tileX + 1; ++x)
        {
            if (x < 0 || x >= Width) continue;

            if (levelData[y][x] == 1)
            {
                handleCollision(player, tiles[y][x]);
            }
        }
    }
}

void Level::handleCollision(Player& player, Platform& platform)
{
    CollisionType col = platform.isColliding(player.collider);

    float platformTop = platform.collider.getGlobalBounds().position.y;
    float playerHeight = player.collider.getSize().y;
    float playerBottom = player.collider.getPosition().y + playerHeight;

    switch (col)
    {
    case CollisionType::Top:
        if (!player.isGrounded && !player.jumping)
        {
            player.verticalVelocity += player.gravity;
            player.position.y = platform.collider.getPosition().y + platform.collider.getSize().y;
        }
        player.isGrounded = true;

        if (playerBottom < platformTop)
        {
            player.position.y++;
        }
        break;

    case CollisionType::Left:
        if (player.currentState == player.climb || player.currentState == player.wallSlide)
            break;

        if (player.facing == Direction::RIGHT)
        {
            player.speed = 0.f;
            player.horizontalVelocity = 0.f;
            player.slideVelocity = 0.f;

            if (player.currentState == player.falling)
            {
                if (player.headSensor.getGlobalBounds().findIntersection(platform.collider.getGlobalBounds()).has_value())
                {
                    player.changeState(player.wallSlide);
                    break;
                }
                else
                {
                    player.position.y = platformTop + player.collider.getSize().y;
                    player.changeState(player.climb);
                    break;
                }
            }
        }
        break;

    case CollisionType::Right:
        if (player.currentState == player.climb || player.currentState == player.wallSlide)
            break;

        if (player.facing == Direction::LEFT)
        {
            player.speed = 0.f;
            player.horizontalVelocity = 0.f;
            player.slideVelocity = 0.f;

            if (player.currentState == player.falling)
            {
                if (player.headSensor.getGlobalBounds().findIntersection(platform.collider.getGlobalBounds()).has_value())
                {
                    player.changeState(player.wallSlide);
                    break;
                }
                else
                {
                    player.position.y = platformTop + player.collider.getSize().y;
                    player.changeState(player.climb);
                    break;
                }
            }
        }
        break;

    case CollisionType::Bottom:
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
