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

    //running
    if (!runLeftTex.loadFromFile("ASSETS\\IMAGES\\RunL.png"))
        std::cout << "Couldn't load run texture\n";
    if (!runRightTex.loadFromFile("ASSETS\\IMAGES\\RunR.png"))
        std::cout << "Couldn't load run texture\n";

    //Crouching and Sliding
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

    if (!slideStartRTex.loadFromFile("ASSETS\\IMAGES\\slide_startR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideStartLTex.loadFromFile("ASSETS\\IMAGES\\slide_startL.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideEndRTex.loadFromFile("ASSETS\\IMAGES\\slide_EndR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideEndLTex.loadFromFile("ASSETS\\IMAGES\\slide_EndL.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideRTex.loadFromFile("ASSETS\\IMAGES\\SlideR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideLTex.loadFromFile("ASSETS\\IMAGES\\SlideL.png"))
        std::cout << "Couldn't load slide texture\n";


    //isJumping
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
    run = new StateRunning();
    jumping = new StateJumping();
    falling = new StateFalling();
    landing = new StateLanding();
    crouchIdle = new StateCrouchIdle();
    crouchWalk = new StateCrouchWalking();
    slide = new StateSlide();

    //Transition states
    idleToWalk = new StateIdleToWalk();
    idleToCrouch = new StateIdleToCrouch();
    crouchToIdle = new StateCrouchToIdle();
    idleToJump = new StateIdleToJump();
    RunToSlide = new StateRunToSlide();
    SlideToRun = new StateSlideToRun();
}

void Player::setUp()
{
    loadTextures();
    setStates();
    currentState = idle;
    idle->enter(*this);
    position = sf::Vector2f{ 0.f, 600.f };
    body.setPosition(position);
    body.setOrigin({ 119, 298 });
    collider.setPosition(position);
    collider.setFillColor(sf::Color::Green);
    collider.setSize(sf::Vector2f{ 100,250 });
    collider.setOrigin({ 50.f, 250.f });
    std::cout << "X: " << position.x << "Y: " << position.y << std::endl;
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

void Player::Render(sf::RenderWindow& m_window, bool m_debug)
{
    if (m_debug)
    {
        m_window.draw(collider);
    }

    m_window.draw(body);
}

void Player::update()
{
    pressingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    pressingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    crouching = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);
    isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    running = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);

    std::cout << "X: " << position.x  << " " << "Y: " << position.y << std::endl;
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


    if (currentState == walk || currentState == run) 
    {
        verticalVelocity = jumpStrength;
        if (isJumping) {
            changeState(jumping);
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
        if(currentState != jumping || currentState != idleToJump || currentState!= slide || currentState != SlideToRun)
        changeState(falling);
    }

    currentState->update(*this);

}

