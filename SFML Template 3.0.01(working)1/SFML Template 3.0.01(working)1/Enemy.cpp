#include "Enemy.h"
#include <iostream>



void Enemy::takeDamage(int damage)
{
    if (!isDead)
    {
        if (!canTakeDamage)
            return;

        health -= damage;
        std::cout << damage << std::endl;

        if (health <= 0)
        {
            health = 0;
            isDead = true;
            std::cout << "THIS ENEMY IS DEAD" << std::endl;
        }

        canTakeDamage = false;
        damageClock.restart();
    }
}

void Enemy::update(Entity& player)
{
    if (!isDead)
    {
        body.setPosition(position);
        collider.setPosition(position);


        if (pressingLeft)
        {
            if (currentState != wallSlide &&
                currentState != slide &&
                currentState != jumping &&
                currentState != falling &&
                currentState != wallJump &&
                currentState != climb)
            {
                !pressingRight;
                facing = Direction::LEFT;
            }
        }

        if (pressingRight)
        {
            if (currentState != wallSlide &&
                currentState != slide &&
                currentState != jumping &&
                currentState != falling &&
                currentState != wallJump &&
                currentState != climb)
            {
                !pressingLeft;
                facing = Direction::RIGHT;
            }
        }

        if (facing == Direction::LEFT)
        {
            headSensor.setPosition(sf::Vector2f{ position.x - 100, position.y - 250 });

            if (currentState != slide && currentState != dropKick)
            {
                hitSensor.setPosition(sf::Vector2f{ position.x - 100, position.y - 200 });
            }
        }
        else
        {
            headSensor.setPosition(sf::Vector2f{ position.x + 50, position.y - 250 });

            if (currentState != slide && currentState != dropKick)
            {
                hitSensor.setPosition(sf::Vector2f{ position.x + 50, position.y - 200 });
            }
        }


        if (currentState == walk || currentState == run)
        {
            verticalVelocity = jumpStrength;
            if (isJumping) {
                if (currentState == wallSlide)
                {
                    changeState(wallJump);
                }
                else
                {
                    changeState(jumping);
                }
            }
        }

        if (player.position.x > position.x)
        {
            pressingLeft = false;
            pressingRight = true;
        }

        if (player.position.x < position.x)
        {
            pressingRight = false;
            pressingLeft = true;
        }

        if (player.position.y < position.y)
        {
            isJumping = true;
        }
        else
        {
            isJumping = false;
        }

        if (player.position.x > position.x + 200 || player.position.x < position.x - 200)
        {
            running = true;
        }
        else
            running = false;


        if (player.crouching)
        {
            crouching = true;
        }
        else
        {
            crouching = false;
        }

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
}
