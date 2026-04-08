#include "Entity.h"
#include "Movementstates.h"
#include<iostream>

void Entity::loadMovementTextures()
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

void Entity::loadCombatTextures()
{
    //punch
    if (!punchLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\punchL.png"))
        std::cout << "Couldnt load puch Texture\n";
    if (!punchRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\punchR.png"))
        std::cout << "Couldnt load punch Texture\n";

    //dropkick
    if (!dropKickLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\dropKickL.png"))
        std::cout << "Couldnt load drop kick Texture\n";
    if (!dropKickRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\dropKickR.png"))
        std::cout << "Couldnt load drop kick Texture\n";

    //take damage
    if (!dmgLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\dmgL.png"))
    {
        std::cout << "Couldn't load damage texture\n";
    }

    if (!dmgRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\dmgR.png"))
    {
        std::cout << "Couldn't load damage texture\n";
    }
     //block
    if (!blockLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\BlockL.png"))
        std::cout << "Couldnt load block Texture\n";
    if (!blockRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\BlockR.png"))
        std::cout << "Couldnt load drop block Texture\n";

    //death
    if (!deathLTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\DeathL.png"))
        std::cout << "Couldnt load death Texture\n";
    if (!deathRTex.loadFromFile("ASSETS\\IMAGES\\PLAYER\\DeathR.png"))
        std::cout << "Couldnt load death Texture\n";
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
    block = new StateBlocking();
    dropKick = new StateDropKick();
    damageState = new SateDamage();
    dead = new StateDeath();
}

void Entity::setUp(sf::Vector2f t_position)
{
    collider.setPosition(position);
    collider.setFillColor(sf::Color::Blue);
    collider.setSize(sf::Vector2f{ 100,250 });
    collider.setOrigin({ 50.f, 250.f });


    loadMovementTextures();
    loadCombatTextures();
    setStates();
    isDead = false;
    canTakeDamage = true;
    currentState = idle;
    idle->enter(*this);
    position = sf::Vector2f{t_position};

    body.setPosition(position);
    body.setOrigin({ 119, 298 });

    headSensor.setPosition(sf::Vector2f{ position.x + 12, position.y + 100 });
    headSensor.setFillColor(sf::Color::Blue);
    headSensor.setSize(sf::Vector2f{ 50 , 10 });

    hitSensor.setPosition(sf::Vector2f{ position.x + 12, position.y + 70 });
    hitSensor.setFillColor(sf::Color::Red);
    hitSensor.setSize(sf::Vector2f{ 50 , 15 });

    health = 100;
}

void Entity::takeDamage(int t_damage)
{
    if (!isDead)
    {
        if (!canTakeDamage)
            return;

        canTakeDamage = false;
        health -= t_damage;
        changeState(damageState);
        std::cout << t_damage << std::endl;

        if (health <= 0)
        {
            health = 0;
            changeState(dead);
        }
    }
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

void Entity::Render(sf::RenderWindow& m_window, bool mapView)
{
    if (mapView)
    {
        if (!isDead)
        {
            m_window.draw(collider);
        }

    }
    else
    {
       m_window.draw(body);
    }
}