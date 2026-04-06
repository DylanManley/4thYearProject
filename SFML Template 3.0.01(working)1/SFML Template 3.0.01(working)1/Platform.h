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
	void setup(sf::Texture& texture, sf::Vector2f position, sf::Vector2f size, int newId);
	CollisionType isColliding(sf::RectangleShape& playerCol);
	void Render(sf::RenderWindow& m_window, bool m_debug);
	sf::RectangleShape collider;
	sf::Color grey{ 158,158,158 };
	int id = 0;

private:
	sf::Sprite* platSprite = nullptr;
	sf::Vector2f size;
};
