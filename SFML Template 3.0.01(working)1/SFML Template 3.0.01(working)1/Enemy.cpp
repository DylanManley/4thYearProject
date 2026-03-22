#include "Enemy.h"
#include <iostream>


void Enemy::update(Entity& player)
{
    float xDistance = player.position.x - position.x;

    if (isDead)
    {
        return;
    }
    
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
        damageClock.stop();
        damageClock.reset();
    }

    switch (aiState)
    {
    case AI_STATE::PATROL:

        if (!clockRunning)
        {
            patrolClock.start();
            pressingLeft = true;
            clockRunning = true;
        }

        if (patrolClock.getElapsedTime().asSeconds() >= 2.0f)
        {
            pressingLeft = false;
            pressingRight = false;
        }

        if (patrolClock.getElapsedTime().asSeconds() >= 3.5f)
        {
            if (facing == Direction::LEFT)
            {
                pressingRight = true;
            }
            else
            {
                pressingLeft = true;
            }
            patrolClock.restart();
        }

        if (abs(xDistance) < 200)
        {
            aiState = AI_STATE::CHASE;
            patrolClock.stop();
        }
        break;
    case AI_STATE::CHASE:
        if (player.position.x > position.x)
        {
            if (xDistance < 100 && isGrounded)
            {
                attacking = true;
            }
            else
            {
                attacking = false;
                pressingLeft = false;
                pressingRight = true;
            }
        }

        if (player.position.x < position.x)
        {
            if (xDistance > -100 && isGrounded)
            {
                attacking = true;
            }
            else
            {
                attacking = false;
                pressingRight = false;
                pressingLeft = true;
            }
        }

        if (!isGrounded)
        {
            if (player.position.y > position.y + 250 && xDistance > -400 || player.position.y > position.y + 250 && xDistance < 400)
            {
                attacking = true;
            }
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
        break;
    default:
        break;
    }

    currentState->update(*this);
}
