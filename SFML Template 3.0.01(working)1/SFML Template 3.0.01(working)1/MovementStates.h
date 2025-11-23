#include "Player.h"
#include "StateMachine.h"


//BASE STATES
class StateIdle : public StateMachine
{
public:
    void enter(Player& p) override
    {
        p.speed = 3;
        if (p.facing == Direction::RIGHT)
        {
            p.body.setTexture(p.idleRightTex);
        }
        else
        {
            p.body.setTexture(p.idleLeftTex);
        }
    }

    void update(Player& p) override
    {
        p.animate(20, 238, 298);
        if (p.pressingRight || p.pressingLeft)
        {
            if (!p.running)
            {
                p.changeState(p.idleToWalk);
            }
            else
            {
                p.changeState(p.run);
            }
        }

        if (p.crouching) {
            p.changeState(p.idleToCrouch);
        }

    }
};


class StateWalking : public StateMachine
{
public:
    void enter(Player& p) override
    {
        p.speed = 3;

        if (p.facing == Direction::RIGHT)
            p.body.setTexture(p.walkRightTex);
        else
            p.body.setTexture(p.walkLeftTex);

        p.currentFrame = 0;
    }

    void update(Player& p) override
    {
        p.animate(20, 238, 298);

        if (p.facing == Direction::RIGHT)
        {
            p.body.setTexture(p.walkRightTex);
            p.position.x += p.speed;

            if (!p.pressingRight)
            {
                p.changeState(p.idle);
            }
        }
        else
        {
            p.body.setTexture(p.walkLeftTex);
            p.position.x -= p.speed;

            if (!p.pressingLeft)
            {
                p.changeState(p.idle);
            }
        }

        if (p.crouching) {
            p.changeState(p.idleToCrouch);
        }

        if (p.running)
        {
            p.changeState(p.run);
        }

        if (!p.isGrounded)
        {
            p.changeState(p.falling);
        }
    }
    
};

class StateRunning : public StateMachine
{
public:
    void enter(Player& p) override
    {
        p.speed = 15;

        p.currentFrame = 0;
        if (p.facing == Direction::RIGHT)
            p.body.setTexture(p.runRightTex);
        else
            p.body.setTexture(p.runLeftTex);
    }

    void update(Player& p) override
    {
        p.animate(15, 238, 298);

        if (p.facing == Direction::RIGHT)
        {
            p.body.setTexture(p.runRightTex);
            p.position.x += p.speed;

            if (!p.pressingRight)
            {
                p.changeState(p.idle);
            }
        }
        else
        {
            p.body.setTexture(p.runLeftTex);
            p.position.x -= p.speed;

            if (!p.pressingLeft)
            {
                p.changeState(p.idle);
            }
        }

        if (!p.running)
        {
            p.changeState(p.walk);
        }

        if (p.crouching) {
            //Slide
        }
    }
};

//JUMPING STATES
class StateJumping : public StateMachine
{
public:
    void enter(Player& p) override
    {
        if (p.facing == Direction::RIGHT)
        {
            p.horizontalVelocity = p.speed;
        }
        else
        {
            p.horizontalVelocity = -p.speed;
        }

        if (p.facing == Direction::RIGHT)
        {
            p.body.setTexture(p.JumpRTex);
        }
        else
        {
            p.body.setTexture(p.JumpLTex);
        }
        p.currentFrame = 0;
        //p.isGrounded = false;
    }

    void update(Player& p) override
    {
        p.animate(4, 238, 298, false);

        if (p.pressingRight) p.horizontalVelocity += p.airAcceleration;
        if (p.pressingLeft)  p.horizontalVelocity -= p.airAcceleration;

        if (!p.pressingRight && !p.pressingLeft)
            p.horizontalVelocity *= (1.f - p.airFriction);

        p.position.x += p.horizontalVelocity;

        p.verticalVelocity += p.gravity;
        p.position.y += p.verticalVelocity;

 
        if (p.verticalVelocity > 0)
        {
            p.currentFrame = 0;
            p.changeState(p.falling);
        }
    }
};

class StateFalling : public StateMachine
{
public:
    void enter(Player& p) override
    {
        if (p.facing == Direction::RIGHT)
        {
            p.body.setTexture(p.FallRTex);
        }
        else
        {
            p.body.setTexture(p.FallLTex);
        }

        p.currentFrame = 0;
    }

    void update(Player& p) override
    {
        p.animate(3, 238, 298, true);

        if (p.pressingRight) p.horizontalVelocity += p.airAcceleration;
        if (p.pressingLeft)  p.horizontalVelocity -= p.airAcceleration;

        if (!p.pressingRight && !p.pressingLeft)
            p.horizontalVelocity *= (1.f - p.airFriction);

        p.position.x += p.horizontalVelocity;


        p.verticalVelocity += p.gravity;
        p.position.y += p.verticalVelocity;


        // Landing check
        if (p.isGrounded)
        {
            p.verticalVelocity = 0;
            p.currentFrame = 0;
            p.changeState(p.landing);
        }
    }
};

class StateLanding : public StateMachine
{
public:
    void enter(Player& p) override
    {

        if (p.facing == Direction::RIGHT)
        {
            p.body.setTexture(p.LandRTex);
        }
        else
        {
            p.body.setTexture(p.LandLTex);
        }
        p.currentFrame = 0;
    }

    void update(Player& p) override
    {
        if (p.animate(4, 238, 298, false))
        {
            p.horizontalVelocity = 0.f;

            if (p.pressingRight)
                p.changeState(p.walk);
            else if (p.pressingLeft)
                p.changeState(p.walk);
            else
                p.changeState(p.idle);

            p.currentFrame = 0;
        }
    }
};

//CROUCH STATES
class StateCrouchIdle : public StateMachine
{
public:
    void enter(Player& p) override
    {
        p.body.setTexture(p.crouchTex);
    }

    void update(Player& p) override
    {
        p.animate(5, 238, 298);
        if (p.pressingRight || p.pressingLeft)
        {
            p.changeState(p.crouchWalk);
        }

        if (p.crouching)
        {
            p.changeState(p.crouchToIdle);
        }
    }
};

class StateCrouchWalking : public StateMachine
{
public:
    void enter(Player& p) override
    {
        if (p.facing == Direction::RIGHT)
            p.body.setTexture(p.cWalkRTex);
        else
            p.body.setTexture(p.cWalkLTex);

        p.currentFrame = 0;
    }

    void update(Player& p) override
    {
        p.animate(20, 238, 298);

        if (p.facing == Direction::RIGHT)
        {
            p.body.setTexture(p.cWalkRTex);
            p.position.x += p.speed;

            if (!p.pressingRight)
            {
                p.changeState(p.crouchIdle);
            }
        }
        else
        {
            p.body.setTexture(p.cWalkLTex);
            p.position.x -= p.speed;

            if (!p.pressingLeft)
            {
                p.changeState(p.crouchIdle);
            }
        }

        if (p.crouching) {
            p.changeState(p.crouchToIdle);
        }
    }
};



//TRANSITION STATES
class StateIdleToWalk : public StateMachine
{
public:
    void enter(Player& p) override
    {
        p.currentFrame = 0;
        if (p.facing == Direction::LEFT)
        {
            p.body.setTexture(p.idleToWalkLTex);
        }
        else
        {
            p.body.setTexture(p.idleToWalkRTex);
        }
    }

    void update(Player& p) override
    {
        if (p.animate(3, 238, 298, false))
        {
            p.changeState(p.walk);
            p.currentFrame = 0;
        }
    }
};

class StateIdleToCrouch : public StateMachine
{
public:
    void enter(Player& p) override
    {
        p.collider.setScale({ 1, 0.6 });
        p.currentFrame = 0;
        p.body.setTexture(p.crouchDownTex);
    }

    void update(Player& p) override
    {
        p.speed = 1;
        if (p.animate(5, 238, 298, false))
        {
            p.changeState(p.crouchIdle);
        }
    }
};

class StateCrouchToIdle : public StateMachine
{
public:
    void enter(Player& p) override
    {
        p.collider.setScale({ 1, 1 });
        p.currentFrame = 0;
        p.body.setTexture(p.standUpTex);
    }

    void update(Player& p) override
    {
        p.speed = 3;
        if (p.animate(5, 238, 298, false))
        {
            p.changeState(p.idle);
        }
    }
};

class StateIdleToJump : public StateMachine
{
public:
    void enter(Player& p) override
    {
        p.currentFrame = 0;
        if (p.facing == Direction::LEFT)
        {
            p.body.setTexture(p.JumpStartL);
        }
        else
        {
            p.body.setTexture(p.JumpStartR);
        }
    }

    void update(Player& p) override
    {
        if (p.animate(3, 238, 298, false))
        {
            p.verticalVelocity = p.jumpStrength;
            p.changeState(p.jumping);
            p.currentFrame = 0;
        }
    }
};