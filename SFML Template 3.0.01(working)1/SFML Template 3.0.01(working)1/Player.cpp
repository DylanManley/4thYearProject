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

    if (!JumpRight.loadFromFile("ASSETS\\IMAGES\\JumpRight.png"))
    {
        std::cout << "Couldn't load jump texture\n";
    }
    if (!FallRight.loadFromFile("ASSETS\\IMAGES\\FallingRight.png"))
    {
        std::cout << "Couldn't load jump texture\n";
    }
    if (!LandRight.loadFromFile("ASSETS\\IMAGES\\LandRight.png"))
    {
        std::cout << "Couldn't load jump texture\n";
    }

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
    bool Jumping = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

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

        if (Jumping)
        {
            verticalVelocity = jumpStrength;
            currentFrame = 0;
            currentState = MovementState::JUMPING;
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

        if (Jumping)
        {
            verticalVelocity = jumpStrength;

            if (pressingRight)
                horizontalVelocity = speed;
            else if (pressingLeft)
                horizontalVelocity = -speed;
            else
                horizontalVelocity = 0;

            currentFrame = 0;
            currentState = MovementState::JUMPING;
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

        if (Jumping)
        {
            verticalVelocity = jumpStrength;

            if (pressingRight)
                horizontalVelocity = speed;
            else if (pressingLeft)
                horizontalVelocity = -speed;
            else
                horizontalVelocity = 0;

            currentFrame = 0;
            currentState = MovementState::JUMPING;
        }

        break;

    case MovementState::JUMPING:
        body.setTexture(JumpRight);
        animate(2, 238, 298, false);


        if (pressingRight)  horizontalVelocity += airAcceleration;
        if (pressingLeft)   horizontalVelocity -= airAcceleration;


        if (!pressingRight && !pressingLeft)
            horizontalVelocity *= (1.f - airFriction);

        position.x += horizontalVelocity;

        verticalVelocity += gravity;
        position.y += verticalVelocity;
        body.setPosition(position);

        if (verticalVelocity > 0)
        {
            currentFrame = 0;
            currentState = MovementState::FALLING;
        }

        break;

    case MovementState::FALLING:
        body.setTexture(FallRight);

        animate(2, 238, 298, true);

        if (pressingRight)  horizontalVelocity += airAcceleration;
        if (pressingLeft)   horizontalVelocity -= airAcceleration;


        if (!pressingRight && !pressingLeft)
            horizontalVelocity *= (1.f - airFriction);

        position.x += horizontalVelocity;

        verticalVelocity += gravity;
        position.y += verticalVelocity;
        body.setPosition(position);

        if (position.y >= groundY)
        {
            position.y = groundY;
            body.setPosition(position);

            verticalVelocity = 0;
            currentFrame = 0;
            currentState = MovementState::LANDING;
        }
        break;

    case MovementState::LANDING:
        body.setTexture(LandRight);

        if (animate(2, 238, 298, false))
        {
            horizontalVelocity = 0.f;

            if (pressingRight)
                currentState = MovementState::WALK_RIGHT;
            else if (pressingLeft)
                currentState = MovementState::WALK_LEFT;
            else
                currentState = MovementState::IDLE;

            currentFrame = 0;
        }
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
        if (animate(2, 238, 298, false))
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

