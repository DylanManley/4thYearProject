#include "Platform.h"

void Platform::setup(sf::Texture &texture, sf::Vector2f position, sf::Vector2f colliderSize)
{
    platSprite = new sf::Sprite{ texture };
    platSprite->setTexture(texture, true);
    platSprite->setPosition(position);
    
    collider.setSize(sf::Vector2f(texture.getSize()));
    collider.setFillColor(sf::Color::Green);
    collider.setPosition(position);
}

CollisionType Platform::isColliding(sf::RectangleShape& playerCol)
{
    sf::FloatRect playerBounds = playerCol.getGlobalBounds();
    sf::FloatRect platformBounds = collider.getGlobalBounds();

    if (!playerBounds.findIntersection(platformBounds))
        return CollisionType::None;

    // Player bounds
    sf::Vector2f playPos = playerBounds.position;
    sf::Vector2f playSize = playerBounds.size;
    float playerTop = playPos.y;
    float playerBottom = playPos.y + playSize.y;
    float playerLeft = playPos.x;
    float playerRight = playPos.x + playSize.x;

    // Platform bounds
    sf::Vector2f platPos = platformBounds.position;
    sf::Vector2f platSize = platformBounds.size;
    float platformTop = platPos.y;
    float platformBottom = platPos.y + platSize.y;
    float platformLeft = platPos.x;
    float platformRight = platPos.x + platSize.x;

    // Collisions
    float collideTop = playerBottom - platformTop;
    float collideBottom = platformBottom - playerTop;
    float collideLeft = playerRight - platformLeft;
    float collideRight = platformRight - playerLeft;

    float overlapX = std::min(collideLeft, collideRight);
    float overlapY = std::min(collideTop, collideBottom);

    if (overlapY < overlapX)
        return (collideTop < collideBottom) ? CollisionType::Top : CollisionType::Bottom;
    else
        return (collideLeft < collideRight) ? CollisionType::Left : CollisionType::Right;
}

void Platform::Render(sf::RenderWindow& m_window, bool m_debug)
{
    m_window.draw(*platSprite);

    if (m_debug)
    {
        m_window.draw(collider);
    }
}
