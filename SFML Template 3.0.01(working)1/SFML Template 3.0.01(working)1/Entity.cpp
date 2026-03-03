#include "Entity.h"
#include "Movementstates.h"
#include<iostream>

void Entity::loadMovementTextures()
{
    // Load all movement textures

    //Idle and Walk
    if (!idleLeftTex.loadFromFile("ASSETS\\IMAGES\\Player\\IdleLeft.png"))
        std::cout << "Couldn't load Idle texture\n";
    if (!idleRightTex.loadFromFile("ASSETS\\IMAGES\\Player\\IdleRight.png"))
        std::cout << "Couldn't load Idle texture\n";
    if (!idleToWalkLTex.loadFromFile("ASSETS\\IMAGES\\Player\\IdleToWalkL.png"))
        std::cout << "Couldn't load IdleToWalk texture\n";
    if (!idleToWalkRTex.loadFromFile("ASSETS\\IMAGES\\Player\\IdleToWalkR.png"))
        std::cout << "Couldn't load IdleToWalk texture\n";
    if (!walkRightTex.loadFromFile("ASSETS\\IMAGES\\Player\\Walk_Right.png"))
        std::cout << "Couldn't load Walk texture\n";
    if (!walkLeftTex.loadFromFile("ASSETS\\IMAGES\\Player\\Walk_Left.png"))
        std::cout << "Couldn't load Walk texture\n";

    //running
    if (!runLeftTex.loadFromFile("ASSETS\\IMAGES\\Player\\RunL.png"))
        std::cout << "Couldn't load run texture\n";
    if (!runRightTex.loadFromFile("ASSETS\\IMAGES\\Player\\RunR.png"))
        std::cout << "Couldn't load run texture\n";

    //Crouching and Sliding
    if (!crouchDownTex.loadFromFile("ASSETS\\IMAGES\\Player\\IdleToCrouch.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!standUpTex.loadFromFile("ASSETS\\IMAGES\\Player\\CrouchToIdle.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!crouchTex.loadFromFile("ASSETS\\IMAGES\\Player\\CrouchIdle.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!cWalkRTex.loadFromFile("ASSETS\\IMAGES\\Player\\CrouchWalkRight.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!cWalkLTex.loadFromFile("ASSETS\\IMAGES\\Player\\CrouchWalkLeft.png"))
        std::cout << "Couldn't load Crouch texture\n";

    if (!slideStartRTex.loadFromFile("ASSETS\\IMAGES\\Player\\slide_startR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideStartLTex.loadFromFile("ASSETS\\IMAGES\\Player\\slide_startL.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideEndRTex.loadFromFile("ASSETS\\IMAGES\\Player\\slide_EndR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideEndLTex.loadFromFile("ASSETS\\IMAGES\\Player\\slide_EndL.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideRTex.loadFromFile("ASSETS\\IMAGES\\Player\\SlideR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideLTex.loadFromFile("ASSETS\\IMAGES\\Player\\SlideL.png"))
        std::cout << "Couldn't load slide texture\n";


    //isJumping
    if (!JumpStartL.loadFromFile("ASSETS\\IMAGES\\Player\\JumpStartL.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!JumpLTex.loadFromFile("ASSETS\\IMAGES\\Player\\JumpL.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!JumpStartR.loadFromFile("ASSETS\\IMAGES\\Player\\JumpStartR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!JumpRTex.loadFromFile("ASSETS\\IMAGES\\Player\\JumpR.png"))
        std::cout << "Couldn't load jump texture\n";

    //Falling and Landing
    if (!FallRTex.loadFromFile("ASSETS\\IMAGES\\Player\\FallingR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!LandRTex.loadFromFile("ASSETS\\IMAGES\\Player\\LandR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!FallLTex.loadFromFile("ASSETS\\IMAGES\\Player\\FallingL.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!LandLTex.loadFromFile("ASSETS\\IMAGES\\Player\\LandL.png"))
        std::cout << "Couldn't load jump texture\n";

    //WallSliding
    if (!WallSlideStartRTex.loadFromFile("ASSETS\\IMAGES\\Player\\wallSlideRStart.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!WallSlideStartLTex.loadFromFile("ASSETS\\IMAGES\\Player\\wallSlideLStart.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallSlideREndTex.loadFromFile("ASSETS\\IMAGES\\Player\\wallSlideREnd.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!WallSlideLEndTex.loadFromFile("ASSETS\\IMAGES\\Player\\wallSlideLEnd.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallSlideRTex.loadFromFile("ASSETS\\IMAGES\\Player\\wallSlideR.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallSlideLTex.loadFromFile("ASSETS\\IMAGES\\Player\\wallSlideL.png"))
        std::cout << "Couldn't load wall jump texture\n";

    //wallJumping
    if (!wallJumpRTex.loadFromFile("ASSETS\\IMAGES\\Player\\wallJumpR.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallJumpLTex.loadFromFile("ASSETS\\IMAGES\\Player\\wallJumpL.png"))
        std::cout << "Couldn't load wall jump texture\n";

    //wallClimb
    if (!climbLTex.loadFromFile("ASSETS\\IMAGES\\Player\\climbL.png"))
        std::cout << "Couldnt load climb Texture\n";
    if (!climbRTex.loadFromFile("ASSETS\\IMAGES\\Player\\climbR.png"))
        std::cout << "Couldnt load climb Texture\n";

}

void Entity::loadCombatTextures()
{
    if (!punchLTex.loadFromFile("ASSETS\\IMAGES\\Player\\punchL.png"))
        std::cout << "Couldnt load puch Texture\n";
    if (!punchRTex.loadFromFile("ASSETS\\IMAGES\\Player\\punchR.png"))
        std::cout << "Couldnt load punch Texture\n";
    if (!dropKickLTex.loadFromFile("ASSETS\\IMAGES\\Player\\dropKickL.png"))
        std::cout << "Couldnt load drop kick Texture\n";
    if (!dropKickRTex.loadFromFile("ASSETS\\IMAGES\\Player\\dropKickR.png"))
        std::cout << "Couldnt load drop kick Texture\n";
    if (!deathLTex.loadFromFile("ASSETS\\IMAGES\\Player\\DeathL.png"))
        std::cout << "Couldnt load drop kick Texture\n";
    if (!deathRTex.loadFromFile("ASSETS\\IMAGES\\Player\\DeathR.png"))
        std::cout << "Couldnt load drop kick Texture\n";
}

void Entity::setStates()
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
    dead = new StateDeath();
}

void Entity::setUp()
{
    loadMovementTextures();
    loadCombatTextures();
    setStates();
    currentState = idle;
    idle->enter(*this);
    position = sf::Vector2f{ 300.f, 1530.f };

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

bool Entity::animate(int frameCount, int frameWidth, int frameHeight, bool loop)
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

void Entity::changeState(StateMachine* newState)
{
    currentState = newState;
    currentFrame = 0;
    currentState->enter(*this);
}

void Entity::Render(sf::RenderWindow& m_window, bool m_debug)
{
    if (m_debug)
    {
        m_window.draw(collider);
        m_window.draw(headSensor);
        m_window.draw(hitSensor);
    }

    m_window.draw(body);
}