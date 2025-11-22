#pragma once
#include "SFML/Graphics.hpp"

class Platform
{
public:
	void setup(sf::Texture &texture, sf::Vector2f position, sf::Vector2f size);
	bool isColliding(sf::RectangleShape& playerCol, sf::RectangleShape& collider);
	void Render(sf::RenderWindow& m_window);
	sf::RectangleShape collider;

private:
	sf::Sprite* platSprite = nullptr;
	sf::Vector2f size;
};
