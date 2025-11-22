#include "Platform.h"

void Platform::setup(sf::Texture &texture, sf::Vector2f position, sf::Vector2f colliderSize)
{
    platSprite = new sf::Sprite{ texture };
    platSprite->setTexture(texture, true);
    platSprite->setPosition(position);
    collider.setSize(colliderSize);
    collider.setFillColor(sf::Color::Green);
    collider.setOrigin(sf::Vector2f{ position.x, position.y - 1170 });
}

bool Platform::isColliding(sf::RectangleShape& playerCol, sf::RectangleShape& collider)
{
    if (playerCol.getGlobalBounds().findIntersection(collider.getGlobalBounds()))
    {
        return true;
    }

    return false;
}

void Platform::Render(sf::RenderWindow& m_window)
{
    m_window.draw(*platSprite);
    m_window.draw(collider);
}
