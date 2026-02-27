#include "player.h"

void Player::update()
{
    pressingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    pressingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    crouching = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);
    isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    running = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
    attacking = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    body.setPosition(position);
    collider.setPosition(position);

    if (pressingLeft)
    {
        !pressingRight;
        facing = Direction::LEFT;
    }

    if (pressingRight)
    {
        !pressingLeft;
        facing = Direction::RIGHT;
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
            if(currentState == wallSlide)
            {
              changeState(wallJump);
            }
            else
            {
                changeState(jumping);
            }
        }
    }

    if (currentState == idle) {
        if (isJumping) {
            changeState(idleToJump);
            isJumping = false;
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

    currentState->update(*this);

}

