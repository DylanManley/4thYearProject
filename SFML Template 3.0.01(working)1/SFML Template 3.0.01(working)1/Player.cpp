#include "player.h"
#include <iostream>

void Player::update()
{

    if (!isDead)
    {
        pressingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
        pressingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
        crouching = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);
        isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        running = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
        attacking = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        blocking = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
        bool suicide = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P);

        std::cout << "Pos X: " << position.x << " Pos Y: " << position.y << std::endl;
        body.setPosition(position);
        collider.setPosition(position);

        healthBarBg.setPosition(sf::Vector2f{ position.x - collider.getSize().x, position.y - collider.getSize().y - 30 });
        healthBar.setPosition(sf::Vector2f{ position.x - collider.getSize().x, position.y - collider.getSize().y - 25});

        healthBar.setSize({ 150.f * (health / 100.f), 10.f });


        if (pressingLeft)
        {
            if (currentState != wallSlide &&
                currentState != slide &&
                currentState != jumping &&
                currentState != falling &&
                currentState != wallJump &&
                currentState != climb)
            {
                pressingRight = false;
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
                pressingLeft = false;
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
                currentState != dropKick &&
                currentState != dead)
            {
                collider.setScale({ 1, 1 });
                changeState(falling);
            }
        }

        if (suicide)
        {
            changeState(dead);
        }

        if (!canTakeDamage && damageClock.getElapsedTime().asSeconds() >= 1.0f)
        {
            canTakeDamage = true;
            damageClock.stop();
            damageClock.reset();
        }

        currentState->update(*this);
    }

}

