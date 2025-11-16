#include "Movementstates.h"
#include <iostream>

void Player::loadTextures()
{
    // Load all textures

    //Idle and Walk
    if (!idleLeftTex.loadFromFile("ASSETS\\IMAGES\\IdleLeft.png"))
        std::cout << "Couldn't load Idle texture\n";
    if (!idleRightTex.loadFromFile("ASSETS\\IMAGES\\IdleRight.png"))
        std::cout << "Couldn't load Idle texture\n";
    if (!idleToWalkLTex.loadFromFile("ASSETS\\IMAGES\\IdleToWalkL.png"))
        std::cout << "Couldn't load IdleToWalk texture\n";
    if (!idleToWalkRTex.loadFromFile("ASSETS\\IMAGES\\IdleToWalkR.png"))
        std::cout << "Couldn't load IdleToWalk texture\n";
    if (!walkRightTex.loadFromFile("ASSETS\\IMAGES\\Walk_Right.png"))
        std::cout << "Couldn't load Walk texture\n";
    if (!walkLeftTex.loadFromFile("ASSETS\\IMAGES\\Walk_Left.png"))
        std::cout << "Couldn't load Walk texture\n";

    //
    if (!crouchDownTex.loadFromFile("ASSETS\\IMAGES\\IdleToCrouch.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!standUpTex.loadFromFile("ASSETS\\IMAGES\\CrouchToIdle.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!crouchTex.loadFromFile("ASSETS\\IMAGES\\CrouchIdle.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!cWalkRTex.loadFromFile("ASSETS\\IMAGES\\CrouchWalkRight.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!cWalkLTex.loadFromFile("ASSETS\\IMAGES\\CrouchWalkLeft.png"))
        std::cout << "Couldn't load Crouch texture\n";

    //Jumping
    if (!JumpStartL.loadFromFile("ASSETS\\IMAGES\\JumpStartL.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!JumpLTex.loadFromFile("ASSETS\\IMAGES\\JumpL.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!JumpStartR.loadFromFile("ASSETS\\IMAGES\\JumpStartR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!JumpRTex.loadFromFile("ASSETS\\IMAGES\\JumpR.png"))
        std::cout << "Couldn't load jump texture\n";

    //Falling and Landing
    if (!FallRTex.loadFromFile("ASSETS\\IMAGES\\FallingR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!LandRTex.loadFromFile("ASSETS\\IMAGES\\LandR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!FallLTex.loadFromFile("ASSETS\\IMAGES\\FallingL.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!LandLTex.loadFromFile("ASSETS\\IMAGES\\LandL.png"))
        std::cout << "Couldn't load jump texture\n";
}

void Player::setStates()
{
    idle = new StateIdle();
    walk = new StateWalking();
    jumping = new StateJumping();
    falling = new StateFalling();
    landing = new StateLanding();
    crouchIdle = new StateCrouchIdle();
    crouchWalk = new StateCrouchWalking();

    //Transition states
    idleToWalk = new StateIdleToWalk();
    idleToCrouch = new StateIdleToCrouch();
    crouchToIdle = new StateCrouchToIdle();
    idleToJump = new StateIdleToJump();
}

void Player::setUp()
{
    loadTextures();
    setStates();
    currentState = idle;
    idle->enter(*this);
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
        timer -= frameTime;
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

void Player::changeState(StateMachine* newState)
{
    currentState = newState;
    currentFrame = 0;
    currentState->enter(*this);
}

void Player::update()
{
    pressingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    pressingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    crouching = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);
    Jumping = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

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


    if (currentState == walk) 
    {
        if (Jumping) {
            verticalVelocity = jumpStrength;
            changeState(jumping);
        }
    }

    if (currentState == idle) {
        if (Jumping) {
            changeState(idleToJump);
            Jumping = false;
        }
    }

    currentState->update(*this);

}

