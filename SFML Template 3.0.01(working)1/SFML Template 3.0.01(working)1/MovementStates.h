#include "Entity.h"
#include "Enemy.h"
#include "StateMachine.h"


//BASE STATES
class StateIdle : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.speed = 3;
        if (e.facing == Direction::RIGHT)
        {
            e.body.setTexture(e.idleRightTex);
        }
        else
        {
            e.body.setTexture(e.idleLeftTex);
        }

        e.hitSensor.setSize(sf::Vector2f{ 50 , 15 });
    }

    void update(Entity& e) override
    {
        e.animate(20, 238, 298);
        if (e.pressingRight || e.pressingLeft)
        {
            if (!e.running)
            {
                e.changeState(e.idleToWalk);
            }
            else
            {
                e.changeState(e.run);
            }
        }

        if (e.crouching) {
            e.changeState(e.idleToCrouch);
        }

        if (e.attacking)
        {
            e.changeState(e.punch);
        }

        if (e.blocking)
        {
            e.changeState(e.block);
        }

    }
};


class StateWalking : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.speed = 3;

        if (e.facing == Direction::RIGHT)
            e.body.setTexture(e.walkRightTex);
        else
            e.body.setTexture(e.walkLeftTex);

        e.currentFrame = 0;
    }

    void update(Entity& e) override
    {
        e.animate(20, 238, 298);

        if (e.facing == Direction::RIGHT)
        {
            e.body.setTexture(e.walkRightTex);
            e.position.x += e.speed;

            if (!e.pressingRight)
            {
                e.changeState(e.idle);
            }
        }
        else
        {
            e.body.setTexture(e.walkLeftTex);
            e.position.x -= e.speed;

            if (!e.pressingLeft)
            {
                e.changeState(e.idle);
            }
        }

        if (e.crouching) {
            e.changeState(e.idleToCrouch);
        }

        if (e.running)
        {
            e.changeState(e.run);
        }

        if (!e.isGrounded)
        {
            e.changeState(e.falling);
        }

        if (e.attacking)
        {
            e.changeState(e.punch);
        }
    }
    
};

class StateRunning : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.speed = 15;

        e.currentFrame = 0;
        if (e.facing == Direction::RIGHT)
            e.body.setTexture(e.runRightTex);
        else
            e.body.setTexture(e.runLeftTex);
    }

    void update(Entity& e) override
    {
        e.animate(15, 238, 298);

        if (e.facing == Direction::RIGHT)
        {
            e.body.setTexture(e.runRightTex);
            e.position.x += e.speed;

            if (!e.pressingRight)
            {
                e.changeState(e.idle);
            }
        }
        else
        {
            e.body.setTexture(e.runLeftTex);
            e.position.x -= e.speed;

            if (!e.pressingLeft)
            {
                e.changeState(e.idle);
            }
        }

        if (!e.running)
        {
            e.changeState(e.walk);
        }

        if (e.crouching) {
            e.changeState(e.RunToSlide);
        }

        if (e.attacking)
        {
            e.changeState(e.punch);
        }
    }
};

//JUMPING STATES
class StateJumping : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        if (e.facing == Direction::RIGHT)
        {
            e.horizontalVelocity = e.speed;
        }
        else
        {
            e.horizontalVelocity = -e.speed;
        }

        if (e.facing == Direction::RIGHT)
        {
            e.body.setTexture(e.JumpRTex);
        }
        else
        {
            e.body.setTexture(e.JumpLTex);
        }
        e.currentFrame = 0;

    }

    void update(Entity& e) override
    {
        e.animate(4, 238, 298, false);

        if (e.pressingRight) e.horizontalVelocity += e.airAcceleration;
        if (e.pressingLeft)  e.horizontalVelocity -= e.airAcceleration;

        if (!e.pressingRight && !e.pressingLeft)
            e.horizontalVelocity *= (1.f - e.airFriction);

        e.position.x += e.horizontalVelocity;

        e.verticalVelocity += e.gravity;
        e.position.y += e.verticalVelocity;

 
        if (e.verticalVelocity > 0)
        {
            e.isJumping = false;
            e.currentFrame = 0;
            e.changeState(e.falling);
        }
    }
};

class StateFalling : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        if (e.facing == Direction::RIGHT)
        {
            e.body.setTexture(e.FallRTex);
        }
        else
        {
            e.body.setTexture(e.FallLTex);
        }

        e.currentFrame = 0;
    }

    void update(Entity& e) override
    {
        e.animate(3, 238, 298, true);
        e.fallTimer = e.fallTimer + 1;

        e.position.x += e.horizontalVelocity;


        e.verticalVelocity += e.gravity;
        e.position.y += e.verticalVelocity;


        // Landing check
        if (e.isGrounded)
        {
            e.verticalVelocity = 0;
            e.currentFrame = 0;
            e.changeState(e.landing);
        }

        if (e.attacking)
        {
            e.changeState(e.dropKick);
        }
    }
};

class StateLanding : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        if (e.facing == Direction::RIGHT)
        {
            e.body.setTexture(e.LandRTex);
        }
        else
        {
            e.body.setTexture(e.LandLTex);
        }
        e.currentFrame = 0;
    }

    void update(Entity& e) override
    {

        if (e.fallTimer >= e.fatalFall)
        {
            e.changeState(e.dead);
        }
        e.fallTimer = 0;

        if (e.animate(4, 238, 298, false))
        {
            e.horizontalVelocity = 0.f;

            if (e.pressingRight)
                e.changeState(e.walk);
            else if (e.pressingLeft)
                e.changeState(e.walk);
            else
                e.changeState(e.idle);

            e.currentFrame = 0;
        }
    }
};

//CROUCH STATES
class StateCrouchIdle : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.body.setTexture(e.crouchTex);
    }

    void update(Entity& e) override
    {
        e.animate(5, 238, 298);
        if (e.pressingRight || e.pressingLeft)
        {
            e.changeState(e.crouchWalk);
        }

        if (e.crouching)
        {
            e.changeState(e.crouchToIdle);
        }
    }
};

class StateCrouchWalking : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        if (e.facing == Direction::RIGHT)
            e.body.setTexture(e.cWalkRTex);
        else
            e.body.setTexture(e.cWalkLTex);

        e.currentFrame = 0;
    }

    void update(Entity& e) override
    {
        e.animate(20, 238, 298);

        if (e.facing == Direction::RIGHT)
        {
            e.body.setTexture(e.cWalkRTex);
            e.position.x += e.speed;

            if (!e.pressingRight)
            {
                e.changeState(e.crouchIdle);
            }
        }
        else
        {
            e.body.setTexture(e.cWalkLTex);
            e.position.x -= e.speed;

            if (!e.pressingLeft)
            {
                e.changeState(e.crouchIdle);
            }
        }

        if (e.crouching) {
            e.changeState(e.crouchToIdle);
        }
    }
};

class StateSlide : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        if (e.facing == Direction::RIGHT)
            e.body.setTexture(e.slideRTex);
        else
            e.body.setTexture(e.slideLTex);

        e.currentFrame = 0;
        e.slideVelocity = e.speed;

        e.hitSensor.setSize(sf::Vector2f{ 50, 50 });
    }

    void update(Entity& e) override
    {
        e.animate(3, 238, 298);

        if (e.facing == Direction::RIGHT)
        {
            e.position.x += e.slideVelocity;
            e.hitSensor.setPosition(sf::Vector2f{ e.position.x + 100, e.position.y - 50});
            e.hitSensor.setPosition(sf::Vector2f{ e.position.x + 100, e.position.y - 50});
        }
        else
        {
            e.position.x -= e.slideVelocity;
            e.hitSensor.setPosition(sf::Vector2f{e.position.x - 100, e.position.y - 50});
        }

        e.slideVelocity -= e.slideDeceleration;
        if (e.slideVelocity < 0)
            e.slideVelocity = 0;

        if (e.slideVelocity == 0 || !e.crouching && !e.attacking)
        {
            e.changeState(e.SlideToRun);
        }
    }
};

class StateWallSlide : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.fallTimer = 0;
        if (e.facing == Direction::RIGHT)
            e.body.setTexture(e.wallSlideRTex);
        else
            e.body.setTexture(e.wallSlideLTex);

        e.verticalVelocity = 0;

        e.currentFrame = 0;
    }

    void update(Entity& e) override
    {
        e.verticalVelocity += (e.gravity * 0.2);
        e.position.y += e.verticalVelocity;

        e.animate(3, 238, 298);

        if (e.isJumping)
        {
            e.changeState(e.wallJump);
        }

        if (e.isGrounded)
        {
            e.changeState(e.wallSlideEnd);
        }
    }
};

class StateWallJump: public StateMachine
{
public:

    void enter(Entity& e) override
    {
        if (e.facing == Direction::RIGHT)
        {
            e.body.setTexture(e.wallJumpLTex);
            e.facing = Direction::LEFT;
        }
        else
        {
            e.body.setTexture(e.wallJumpRTex);
            e.facing = Direction::RIGHT;
        }

        e.currentFrame = 0;
    }

    void update(Entity& e) override
    {

        if (e.facing == Direction::LEFT)
        {
            e.horizontalVelocity -= 3;
        }
        else
        {
            e.horizontalVelocity += 3;
        }

        e.verticalVelocity -= e.gravity + 1;
        e.position.y += e.verticalVelocity;

        e.position.y += e.verticalVelocity;
        e.position.x += e.horizontalVelocity;




        if (e.animate(3, 238, 298, false))
        {
            e.changeState(e.falling);
            e.currentFrame = 0;
        }
    }
};

class StateClimb : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        if (!e.isDead)
        {
            e.fallTimer = 0;
        }

        if (e.facing == Direction::RIGHT)
        {
            e.body.setTexture(e.climbRTex);
        }
        else
        {
            e.body.setTexture(e.climbLTex);
        }
        e.isGrounded = true;
    }

    void update(Entity& e) override
    {

        if (e.currentFrame < 5)
        {
            e.position.y -= 14;
        }
        
        if (e.currentFrame <= 7)
        {
            if(e.facing == Direction::RIGHT)
            {
                e.position.x += 3;
            }
            else
            {
                e.position.x -= 3;
            }
        }

        if (e.animate(9, 238, 298, false))
        {
            e.changeState(e.idle);
            e.currentFrame = 0;
        }
    }
};



//TRANSITION STATES
class StateIdleToWalk : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.currentFrame = 0;
        if (e.facing == Direction::LEFT)
        {
            e.body.setTexture(e.idleToWalkLTex);
        }
        else
        {
            e.body.setTexture(e.idleToWalkRTex);
        }
    }

    void update(Entity& e) override
    {
        if (e.animate(3, 238, 298, false))
        {
            e.changeState(e.walk);
            e.currentFrame = 0;
        }
    }
};

class StateIdleToCrouch : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.collider.setScale({ 1, 0.6 });
        e.currentFrame = 0;
        e.body.setTexture(e.crouchDownTex);
    }

    void update(Entity& e) override
    {
        e.speed = 1.5;
        if (e.animate(5, 238, 298, false))
        {
            e.changeState(e.crouchIdle);
        }
    }
};

class StateCrouchToIdle : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.collider.setScale({ 1, 1 });
        e.currentFrame = 0;
        e.body.setTexture(e.standUpTex);
    }

    void update(Entity& e) override
    {
        e.speed = 3;
        if (e.animate(5, 238, 298, false))
        {
            e.changeState(e.idle);
        }
    }
};

class StateIdleToJump : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.currentFrame = 0;
        if (e.facing == Direction::LEFT)
        {
            e.body.setTexture(e.JumpStartL);
        }
        else
        {
            e.body.setTexture(e.JumpStartR);
        }
    }

    void update(Entity& e) override
    {
        if (e.animate(3, 238, 298, false))
        {
            e.verticalVelocity = e.jumpStrength;
            e.changeState(e.jumping);
            e.currentFrame = 0;
        }
    }
};

class StateRunToSlide : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.collider.setScale({ 2.2, 0.3 });
        e.currentFrame = 0;
        if (e.facing == Direction::LEFT)
        {
            e.body.setTexture(e.slideStartLTex);
        }
        else
        {
            e.body.setTexture(e.slideStartRTex);
        }
    }

    void update(Entity& e) override
    {
        e.position.x += e.speed;

        if (e.animate(5, 238, 298, false))
        {
            e.changeState(e.slide);
        }
    }

};


class StateSlideToRun : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.collider.setScale({ 1, 1 });

        e.currentFrame = 0;
        if (e.facing == Direction::LEFT)
        {
            e.body.setTexture(e.slideEndLTex);
        }
        else
        {
            e.body.setTexture(e.slideEndRTex);
        }
    }

    void update(Entity& e) override
    {
        if (e.animate(3, 238, 298, false))
        {
            e.changeState(e.run);
        }
    }

};

class StateWallSlideStart : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.currentFrame = 0;
        if (e.facing == Direction::LEFT)
        {
            e.body.setTexture(e.WallSlideStartLTex);
        }
        else
        {
            e.body.setTexture(e.WallSlideStartRTex);
        }
    }

    void update(Entity& e) override
    {
        e.verticalVelocity += (e.gravity * 0.6);
        e.position.y += e.verticalVelocity;

        if (e.animate(3, 238, 298, false))
        {
            e.changeState(e.wallSlide);
        }

        if (e.isGrounded)
        {
            e.changeState(e.wallSlideEnd);
        }
    }

};

class StateWallSlideEnd : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.currentFrame = 0;
        if (e.facing == Direction::LEFT)
        {
            e.body.setTexture(e.WallSlideLEndTex);
        }
        else
        {
            e.body.setTexture(e.wallSlideREndTex);
        }
    }

    void update(Entity& e) override
    {
        if (e.animate(3, 238, 298, false))
        {
            e.changeState(e.idle);
        }
        
        if (e.isGrounded)
        {
            e.changeState(e.idle);
        }
    }

};


//combat states(MOVE TO OWN FILE LATER)
class StatePunch : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.currentFrame = 0;
        if (e.facing == Direction::LEFT)
        {
            e.body.setTexture(e.punchLTex);
        }
        else
        {
            e.body.setTexture(e.punchRTex);
        }
    }

    void update(Entity& e) override
    {
        if (e.animate(7, 238, 298, false))
        {
            e.attacking = false;
            e.changeState(e.idle);
        }
    }
};

class StateDropKick : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.collider.setScale({ 2.2, 0.3 });
        e.currentFrame = 0;
        if (e.facing == Direction::LEFT)
        {
            e.body.setTexture(e.dropKickLTex);
        }
        else
        {
            e.body.setTexture(e.dropKickRTex);
        }

        e.hitSensor.setSize(sf::Vector2f{ 50, 50 });
    }

    void update(Entity& e) override
    {
        e.animate(7, 238, 298, false);


        if (e.facing == Direction::RIGHT)
        {
            e.hitSensor.setPosition(sf::Vector2f{ e.position.x + 100, e.position.y - 50 });
        }
        else
        {
            e.hitSensor.setPosition(sf::Vector2f{ e.position.x - 100, e.position.y - 50 });
        }

        if (e.pressingRight) e.horizontalVelocity += e.airAcceleration;
        if (e.pressingLeft)  e.horizontalVelocity -= e.airAcceleration;

        if (!e.pressingRight && !e.pressingLeft)
            e.horizontalVelocity *= (1.f - e.airFriction);

        e.position.x += e.horizontalVelocity;


        e.verticalVelocity += (e.gravity /2) ;
        e.position.y += e.verticalVelocity;
    
        if (e.isGrounded)
        {
            e.changeState(e.slide);
        }
    }
};

class SateDamage : public StateMachine
{
    void enter(Entity& e) override
    {
        e.currentFrame = 0;
        e.damageClock.start();
        if (e.facing == Direction::LEFT)
        {
            e.body.setTexture(e.dmgLTex);
        }
        else
        {
            e.body.setTexture(e.dmgRTex);
        }
            
    }

    void update(Entity& e)
    {
        e.attacking = false;
        if (e.facing == Direction::LEFT)
        {
            e.position.x = e.position.x + 1;
        }
        else
        {
            e.position.x = e.position.x - 1;
        }
        if (e.animate(8, 238, 298, false))
        {
            e.changeState(e.idle);
        }
    }
};

class StateDeath : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.canTakeDamage = false;
        e.currentFrame = 0;
        if (e.facing == Direction::LEFT)
        {
            e.body.setTexture(e.deathLTex);
        }
        else
        {
            e.body.setTexture(e.deathRTex);
        }
    }

    void update(Entity& e) override
    {
        e.canTakeDamage = false;
        if (e.animate(25, 238, 298, false))
        {
            e.isDead = true;
        }
    }
};

class StateBlocking : public StateMachine
{
public:
    void enter(Entity& e) override
    {
        e.canTakeDamage = false;
        e.currentFrame = 0;
        if (e.facing == Direction::LEFT)
        {
            e.body.setTexture(e.blockLTex);
        }
        else
        {
            e.body.setTexture(e.blockRTex);
        }
    }

    void update(Entity& e) override
    {
        e.canTakeDamage = false;
        e.attacking = false;
        e.animate(4, 238, 298, false);

        if (!e.blocking)
        {
            e.canTakeDamage = true;
            e.changeState(e.idle);
        }
    }
};