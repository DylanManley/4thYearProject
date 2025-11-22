#pragma once
#include "SFML/Graphics.hpp"
enum class CollisionType
{
	None,
	Top,
	Bottom,
	Left,
	Right
};

class Platform
{
public:
	void setup(sf::Texture &texture, sf::Vector2f position, sf::Vector2f size);
	CollisionType isColliding(sf::RectangleShape& playerCol);
	void Render(sf::RenderWindow& m_window);
	sf::RectangleShape collider;

private:
	sf::Sprite* platSprite = nullptr;
	sf::Vector2f size;
};
