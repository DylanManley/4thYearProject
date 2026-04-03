#include "Enemy.h"
#include <iostream>

float Enemy::mClose(float dist) {
    if (dist <= 10) return 1.f;
    if (dist <= 100) return (100.f - dist) / (100.f - 10.f);
    return 0.f;
}

float Enemy::mFar(float dist) {
    if (dist <= 350) return 0.f;
    if (dist <= 450) return (dist - 350.f) / (350.f - 250.f);
    return 0.f;
}

float Enemy::mPlayerAttacking(bool playerAttacking) {
    return playerAttacking ? 1.f : 0.f;
}

float Enemy::fuzzyAttack(float dist) {
    return mClose(dist);
}

float Enemy::fuzzyBlock(float dist, bool playerAttacking) {
    float proximity = mClose(dist);
    float threatBonus = mPlayerAttacking(playerAttacking) * 0.9f;
    return std::min(1.f, proximity + threatBonus);
}

float Enemy::fuzzyDropkick(float dist) {
    return mFar(dist);
}

void Enemy::update(Entity& player)
{
    float dist = std::abs(player.position.x - position.x);

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

        if (abs(dist) < 200)
        {
            aiState = AI_STATE::CHASE;
            patrolClock.stop();
        }
        break;
    case AI_STATE::CHASE:
        if (dist > 50)
        {
            if (player.position.x > position.x) {
                pressingRight = true;
                pressingLeft = false;
            }
            else {
                pressingLeft = true;
                pressingRight = false;
            }
            running = dist > 300;
        }
        else
        {
            pressingLeft = false;
            pressingRight = false;
            running = false;
        }


        if (currentState != wallSlide &&
            currentState != slide &&
            currentState != jumping &&
            currentState != falling &&
            currentState != wallJump &&
            currentState != climb)
        {

            if (player.position.x > position.x)
                facing = Direction::RIGHT;
            else
                facing = Direction::LEFT;
        }


        crouching = player.crouching;
        applyFuzzyResult(player);
        break;
    default:
        break;
    }

    currentState->update(*this);
}

void Enemy::loadMovementTextures()
{
    collider.setFillColor(sf::Color::Red);
    // Load all movement textures

   //Idle and Walk
    if (!idleLeftTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\IdleLeft.png"))
        std::cout << "Couldn't load Idle texture\n";
    if (!idleRightTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\IdleRight.png"))
        std::cout << "Couldn't load Idle texture\n";
    if (!idleToWalkLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\IdleToWalkL.png"))
        std::cout << "Couldn't load IdleToWalk texture\n";
    if (!idleToWalkRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\IdleToWalkR.png"))
        std::cout << "Couldn't load IdleToWalk texture\n";
    if (!walkRightTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\Walk_Right.png"))
        std::cout << "Couldn't load Walk texture\n";
    if (!walkLeftTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\Walk_Left.png"))
        std::cout << "Couldn't load Walk texture\n";

    //running
    if (!runLeftTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\RunL.png"))
        std::cout << "Couldn't load run texture\n";
    if (!runRightTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\RunR.png"))
        std::cout << "Couldn't load run texture\n";

    //Crouching and Sliding
    if (!crouchDownTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\IdleToCrouch.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!standUpTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\CrouchToIdle.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!crouchTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\CrouchIdle.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!cWalkRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\CrouchWalkRight.png"))
        std::cout << "Couldn't load Crouch texture\n";
    if (!cWalkLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\CrouchWalkLeft.png"))
        std::cout << "Couldn't load Crouch texture\n";

    if (!slideStartRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\slide_startR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideStartLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\slide_startL.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideEndRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\slide_EndR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideEndLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\slide_EndL.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\SlideR.png"))
        std::cout << "Couldn't load slide texture\n";
    if (!slideLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\SlideL.png"))
        std::cout << "Couldn't load slide texture\n";


    //isJumping
    if (!JumpStartL.loadFromFile("ASSETS\\IMAGES\\ENEMY\\JumpStartL.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!JumpLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\JumpL.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!JumpStartR.loadFromFile("ASSETS\\IMAGES\\ENEMY\\JumpStartR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!JumpRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\JumpR.png"))
        std::cout << "Couldn't load jump texture\n";

    //Falling and Landing
    if (!FallRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\FallingR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!LandRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\LandR.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!FallLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\FallingL.png"))
        std::cout << "Couldn't load jump texture\n";
    if (!LandLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\LandL.png"))
        std::cout << "Couldn't load jump texture\n";

    //WallSliding
    if (!WallSlideStartRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\wallSlideRStart.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!WallSlideStartLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\wallSlideLStart.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallSlideREndTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\wallSlideREnd.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!WallSlideLEndTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\wallSlideLEnd.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallSlideRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\wallSlideR.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallSlideLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\wallSlideL.png"))
        std::cout << "Couldn't load wall jump texture\n";

    //wallJumping
    if (!wallJumpRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\wallJumpR.png"))
        std::cout << "Couldn't load wallslide texture\n";
    if (!wallJumpLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\wallJumpL.png"))
        std::cout << "Couldn't load wall jump texture\n";

    //wallClimb
    if (!climbLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\climbL.png"))
        std::cout << "Couldnt load climb Texture\n";
    if (!climbRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\climbR.png"))
        std::cout << "Couldnt load climb Texture\n";
}

void Enemy::loadCombatTextures()
{
    //punch
    if (!punchLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\punchL.png"))
        std::cout << "Couldnt load puch Texture\n";
    if (!punchRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\punchR.png"))
        std::cout << "Couldnt load punch Texture\n";

    //dropkick
    if (!dropKickLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\dropKickL.png"))
        std::cout << "Couldnt load drop kick Texture\n";
    if (!dropKickRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\dropKickR.png"))
        std::cout << "Couldnt load drop kick Texture\n";

    //take damage
    if (!dmgLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\dmgL.png"))
    {
        std::cout << "Couldn't load damage texture\n";
    }

    if (!dmgRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\dmgR.png"))
    {
        std::cout << "Couldn't load damage texture\n";
    }
    //block
    if (!blockLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\BlockL.png"))
        std::cout << "Couldnt load block Texture\n";
    if (!blockRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\BlockR.png"))
        std::cout << "Couldnt load drop block Texture\n";

    //death
    if (!deathLTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\DeathL.png"))
        std::cout << "Couldnt load death Texture\n";
    if (!deathRTex.loadFromFile("ASSETS\\IMAGES\\ENEMY\\DeathR.png"))
        std::cout << "Couldnt load death Texture\n";
}

void Enemy::applyFuzzyResult(const Entity& player)
{
    float dist = std::abs(player.position.x - position.x);
    float attackScore = fuzzyAttack(dist);
    float blockScore = fuzzyBlock(dist, player.attacking);
    float dropkickScore = fuzzyDropkick(dist);

    if (!canAttack && attackCooldown.getElapsedTime().asSeconds() > 1.0f)
    {
        canAttack = true;
        attackCooldown.stop();
        attackCooldown.reset();
    }

    if (!canBlock && blockCooldown.getElapsedTime().asSeconds() > 1.5f)
    {
        canBlock = true;
        blockCooldown.stop();
        blockCooldown.reset();
    }

    if (dropkickScore > 0.3f && isGrounded && canAttack)
    {
        attacking = true;
        isJumping = true;
        blocking = false;
        pressingLeft = false;
        pressingRight = false;
        canAttack = false;
        attackCooldown.restart();
        return;
    }

    //block
    if (canBlock && blockScore > attackScore && blockScore > 0.3f)
    {
        blocking = true;
        attacking = false;
        canBlock = false;
        blockCooldown.restart();
        return;
    }

    blocking = false;

    //punch
    if (attackScore > 0.3f && canAttack)
    {
        isJumping = false;
        attacking = true;
        canAttack = false;
        attackCooldown.restart();
        return;
    }
}
