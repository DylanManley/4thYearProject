#include "Enemy.h"
#include <iostream>

void Enemy::setup(sf::Vector2f position, int health)
{
	collider.setPosition(position);
	collider.setFillColor(sf::Color::Red);
	collider.setSize(sf::Vector2f{ 100,250 });
	collider.setOrigin({ 50.f, 250.f });
}

void Enemy::render(sf::RenderWindow& window, bool showDeug)
{
	if (!dead)
	{
		window.draw(collider);
	}
}

void Enemy::takeDamage(int damage)
{
    if (!canTakeDamage || dead)
        return;

    health -= damage;
    std::cout << damage << std::endl;

    if (health <= 0)
    {
        health = 0;
        dead = true;
        std::cout << "THIS ENEMY IS DEAD" << std::endl;
    }

    canTakeDamage = false;
    damageClock.restart();
}

void Enemy::update()
{
    if (!canTakeDamage && damageClock.getElapsedTime().asSeconds() >= 1.0f)
    {
        canTakeDamage = true;
    }

}
