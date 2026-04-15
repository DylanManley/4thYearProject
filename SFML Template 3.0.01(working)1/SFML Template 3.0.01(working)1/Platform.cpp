#include "Platform.h"

void Platform::setup(sf::Texture &texture, sf::Vector2f position, sf::Vector2f colliderSize, int newId)
{
    platSprite = new sf::Sprite{ texture };
    platSprite->setTexture(texture, true);
    platSprite->setPosition(position);
    
    collider.setSize(sf::Vector2f(texture.getSize()));
    collider.setFillColor(grey);
    collider.setPosition(position);

    id = newId;
}

CollisionType Platform::isColliding(sf::RectangleShape& EntityCol)
{
    sf::FloatRect EntityBounds = EntityCol.getGlobalBounds();
    sf::FloatRect platformBounds = collider.getGlobalBounds();

    auto intersection = EntityBounds.findIntersection(platformBounds);
    if (!intersection.has_value())
        return CollisionType::None;

    sf::Vector2f EntPos = EntityBounds.position;
    sf::Vector2f EntSize = EntityBounds.size;
    float EntityTop = EntPos.y;
    float EntityBottom = EntPos.y + EntSize.y;
    float EntityLeft = EntPos.x;
    float EntityRight = EntPos.x + EntSize.x;

    sf::Vector2f platPos = platformBounds.position;
    sf::Vector2f platSize = platformBounds.size;
    float platformTop = platPos.y;
    float platformBottom = platPos.y + platSize.y;
    float platformLeft = platPos.x;
    float platformRight = platPos.x + platSize.x;

    float collideTop = EntityBottom - platformTop;
    float collideBottom = platformBottom - EntityTop;
    float collideLeft = EntityRight - platformLeft;
    float collideRight = platformRight - EntityLeft;

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
