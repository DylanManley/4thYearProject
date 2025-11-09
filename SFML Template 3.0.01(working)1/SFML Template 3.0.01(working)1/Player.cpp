#include "Player.h"
#include <iostream>

void Player::setUp()
{
    // Load all textures
    if (!idleTexture.loadFromFile("ASSETS\\IMAGES\\Idle.png"))
        std::cout << "Couldn't load Idle texture\n";
    if (!idleToWalkTexture.loadFromFile("ASSETS\\IMAGES\\IdleToWalk.png"))
        std::cout << "Couldn't load IdleToWalk texture\n";
    if (!walkRightTexture.loadFromFile("ASSETS\\IMAGES\\Walk_Right.png"))
        std::cout << "Couldn't load Walk texture\n";
    if (!walkLeftTexture.loadFromFile("ASSETS\\IMAGES\\Walk_Left.png"))
        std::cout << "Couldn't load Walk texture\n";

    if (!crouchDownTexture.loadFromFile("ASSETS\\IMAGES\\IdleToCrouch.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!standUpTexture.loadFromFile("ASSETS\\IMAGES\\CrouchToIdle.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!CrouchWalkRight.loadFromFile("ASSETS\\IMAGES\\CrouchWalkRight.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!CrouchWalkLeft.loadFromFile("ASSETS\\IMAGES\\CrouchWalkLeft.png"))
        std::cout << "Couldn't load Crouch texture\n";

    body.setTexture(idleTexture);
    position = sf::Vector2f{ 200.f, 300.f };
    body.setPosition(position);
}

bool Player::animate(int frameCount, int frameWidth, int frameHeight, bool loop)
{
    animationFinished = false;

    float delta = clock.restart().asSeconds();
    timer += delta;

    if (timer >= frameTime)
    {
        timer = 0.0f;
        currentFrame++;

        if (loop)
            currentFrame %= frameCount;
        else if (currentFrame >= frameCount)
        {
            currentFrame = frameCount - 1;
            animationFinished = true;
        }

        body.setTextureRect(sf::IntRect({ currentFrame * frameWidth, 0 }, { frameWidth, frameHeight }));
    }

    return animationFinished;
}

void Player::update()
{
    bool pressingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    bool pressingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    bool crouching = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);

    switch (currentState)
    {
    case MovementState::IDLE:
        body.setTexture(idleTexture);
        animate(20, 238, 298);

        if (!crouching)
        {
            if (pressingRight)
            {
                currentFrame = 0;
                currentState = MovementState::IDLE_TO_WALK;
            }

            if (pressingLeft)
            {
                currentFrame = 0;
                currentState = MovementState::IDLE_TO_WALK;
            }
        }
        else
        {
            currentState = MovementState::IDLE_TO_CROUCH;
            currentFrame = 0;
        }

       
        break;

    case MovementState::WALK_RIGHT:
        body.setTexture(walkRightTexture);
        animate(20, 238, 298);

        if (!pressingRight)
        {
            currentState = MovementState::IDLE;
            currentFrame = 0;
        }
        else
        {
            position.x += speed;
            body.setPosition(position);
        }
        break;

    case MovementState::WALK_LEFT:
        body.setTexture(walkLeftTexture);
        animate(20, 238, 298);

        if (!pressingLeft)
        {
            currentState = MovementState::IDLE;
            currentFrame = 0;
        }
        else
        {
            position.x -= speed;
            body.setPosition(position);
        }

        break;

    case MovementState::JUMPING:
        break;
    case MovementState::CROUCH_IDLE:
        if (!crouching)
        {
            currentState = MovementState::CROUCH_TO_IDLE;
        }

        if (pressingRight)
        {
            currentState = MovementState::CROUCH_WALK_RIGHT;
        }

        if (pressingLeft)
        {
            currentState = MovementState::CROUCH_WALK_LEFT;
        }

        break;
    case MovementState::CROUCH_WALK_RIGHT:
        body.setTexture(CrouchWalkRight);
        animate(20, 238, 298);
        if (!pressingRight)
        {
            currentState = MovementState::CROUCH_IDLE;
            currentFrame = 0;
        }
        else
        {
            position.x += speed;
            body.setPosition(position);
        }
        break;
    case MovementState::CROUCH_WALK_LEFT:
        body.setTexture(CrouchWalkLeft);
        animate(20, 238, 298);
        if (!pressingLeft)
        {
            currentState = MovementState::CROUCH_IDLE;
            currentFrame = 0;
        }
        else
        {
            position.x -= speed;
            body.setPosition(position);
        }
        break;


        //transition states
    case MovementState::IDLE_TO_WALK:
        body.setTexture(idleToWalkTexture);
        if (animate(5, 238, 298, false))
        {
            if(pressingRight)
            currentState = MovementState::WALK_RIGHT;
            if (pressingLeft)
            {
                currentState = MovementState::WALK_LEFT;
            }
            currentFrame = 0;
        }
        break;

    case MovementState::IDLE_TO_CROUCH:
        speed = 1;
        body.setTexture(crouchDownTexture);
        if (animate(5, 238, 298, false))
        {
            currentState = MovementState::CROUCH_IDLE;
        }
        break;

    case MovementState::CROUCH_TO_IDLE:
        speed = 3;
        body.setTexture(standUpTexture);
        if (animate(5, 238, 298, false))
        {
            currentState = MovementState::IDLE;
        }
        break;

    default:
        break;
    }
}

