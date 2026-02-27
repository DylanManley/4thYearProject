#include "Enemy.h"
#include <iostream>



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
    if (!isGrounded)
    {
        if (currentState != jumping &&
            currentState != idleToJump &&
            currentState != landing &&
            currentState != wallSlideStart &&
            currentState != wallSlide &&
            currentState != wallJump &&
            currentState != climb &&
            currentState != dropKick)
        {
            collider.setScale({ 1, 1 });
            changeState(falling);
        }
    }

    if (!canTakeDamage && damageClock.getElapsedTime().asSeconds() >= 0.6f)
    {
        canTakeDamage = true;
    }

    currentState->update(*this);
}
