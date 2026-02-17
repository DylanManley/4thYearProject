#include "Movementstates.h"
#include <iostream>

void Player::loadMovementTextures()
{
    // Load all movement textures

    //Idle and Walk
    if (!idleLeftTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\IdleLeft.png"))
        std::cout << "Couldn't load Idle texture\n";
    if (!idleRightTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\IdleRight.png"))
        std::cout << "Couldn't load Idle texture\n";
    if (!idleToWalkLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\IdleToWalkL.png"))
        std::cout << "Couldn't load IdleToWalk texture\n";
    if (!idleToWalkRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\IdleToWalkR.png"))
        std::cout << "Couldn't load IdleToWalk texture\n";
    if (!walkRightTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\Walk_Right.png"))
        std::cout << "Couldn't load Walk texture\n";
    if (!walkLeftTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\Walk_Left.png"))
        std::cout << "Couldn't load Walk texture\n";

    //running
    if (!runLeftTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\RunL.png"))
        std::cout << "Couldn't load run texture\n";
    if (!runRightTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\RunR.png"))
        std::cout << "Couldn't load run texture\n";

    //Crouching and Sliding
    if (!crouchDownTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\IdleToCrouch.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!standUpTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\CrouchToIdle.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!crouchTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\CrouchIdle.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!cWalkRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\CrouchWalkRight.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!cWalkLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\CrouchWalkLeft.png"))
        std::cout << "Couldn't load Crouch texture\n";

    if (!slideStartRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\slide_startR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideStartLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\slide_startL.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideEndRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\slide_EndR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideEndLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\slide_EndL.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\SlideR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\SlideL.png"))
        std::cout << "Couldn't load slide texture\n";


    //isJumping
    if (!JumpStartL.loadFromFile("ASSETS\\IMAGES\\PLAYER\\JumpStartL.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!JumpLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\JumpL.png"))     
        std::cout << "Couldn't load jump texture\n";
    if (!JumpStartR.loadFromFile("ASSETS\\IMAGES\\PLAYER\\JumpStartR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!JumpRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\JumpR.png"))
        std::cout << "Couldn't load jump texture\n";

    //Falling and Landing
    if (!FallRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\FallingR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!LandRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\LandR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!FallLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\FallingL.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!LandLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\LandL.png"))
        std::cout << "Couldn't load jump texture\n";

    //WallSliding
    if (!WallSlideStartRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\wallSlideRStart.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!WallSlideStartLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\wallSlideLStart.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallSlideREndTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\wallSlideREnd.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!WallSlideLEndTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\wallSlideLEnd.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallSlideRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\wallSlideR.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallSlideLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\wallSlideL.png"))
        std::cout << "Couldn't load wall jump texture\n";

    //wallJumping
    if (!wallJumpRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\wallJumpR.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallJumpLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\wallJumpL.png"))
        std::cout << "Couldn't load wall jump texture\n";

    //wallClimb
    if (!climbLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\climbL.png"))
        std::cout << "Couldnt load climb Texture\n";
    if (!climbRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\climbR.png"))
        std::cout << "Couldnt load climb Texture\n";

}

void Player::loadCombatTextures()
{
    if (!punchLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\punchL.png"))
        std::cout << "Couldnt load puch Texture\n";
    if (!punchRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\punchR.png"))
        std::cout << "Couldnt load punch Texture\n";
    if (!dropKickLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\dropKickL.png"))
        std::cout << "Couldnt load drop kick Texture\n";
    if (!dropKickRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\dropKickR.png"))
        std::cout << "Couldnt load drop kick Texture\n";
}

void Player::setStates()
{
    //Movement States
    idle = new StateIdle();
    walk = new StateWalking();
    run = new StateRunning();
    jumping = new StateJumping();
    falling = new StateFalling();
    landing = new StateLanding();
    crouchIdle = new StateCrouchIdle();
    crouchWalk = new StateCrouchWalking();
    slide = new StateSlide();
    wallSlide = new StateWallSlide();
    climb = new StateClimb();

    //Transition states
    idleToWalk = new StateIdleToWalk();
    idleToCrouch = new StateIdleToCrouch();
    crouchToIdle = new StateCrouchToIdle();
    idleToJump = new StateIdleToJump();
    RunToSlide = new StateRunToSlide();
    SlideToRun = new StateSlideToRun();
    wallSlideStart = new StateWallSlideStart();
    wallSlideEnd = new StateWallSlideEnd();
    wallJump = new StateWallJump();

    //Combat States
    punch = new StatePunch();
    dropKick = new StateDropKick();
}

void Player::setUp()
{
    loadMovementTextures();
    loadCombatTextures();
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
    
    headSensor.setPosition(sf::Vector2f{ position.x + 12, position.y + 100 });
    headSensor.setFillColor(sf::Color::Blue);
    headSensor.setSize(sf::Vector2f{ 50 , 10 });

    hitSensor.setPosition(sf::Vector2f{ position.x + 12, position.y + 70 });
    hitSensor.setFillColor(sf::Color::Red);
    hitSensor.setSize(sf::Vector2f{ 50 , 15 });
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
        m_window.draw(headSensor);
        m_window.draw(hitSensor);
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
    attacking = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

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

