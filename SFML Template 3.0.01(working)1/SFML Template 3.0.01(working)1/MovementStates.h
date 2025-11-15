#include "Player.h"
#include "StateMachine.h"


//BASE STATES
class StateIdle : public StateMachine
{
public:
    void enter(Player& p) override
    {
       p.body.setTexture(p.idleTex);
    }

    void update(Player& p) override
    {
        p.animate(20, 238, 298);
        if (p.pressingRight || p.pressingLeft)
        {
            p.changeState(p.idleToWalk);
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
            p.body.setPosition(p.position);

            if (!p.pressingRight)
            {
                p.changeState(p.idle);
            }
        }
        else
        {
            p.body.setTexture(p.walkLeftTex);
            p.position.x -= p.speed;
            p.body.setPosition(p.position);

            if (!p.pressingLeft)
            {
                p.changeState(p.idle);
            }
        }

        if (p.crouching) {
            p.changeState(p.idleToCrouch);
        }
    }
};

//JUMPING STATES

class StateJumping : public StateMachine
{
public:
    void enter(Player& p) override
    {
        p.body.setTexture(p.JumpRTex);
        p.currentFrame = 0;
    }

    void update(Player& p) override
    {
        p.animate(2, 238, 298, false);

        if (p.pressingRight) p.horizontalVelocity += p.airAcceleration;
        if (p.pressingLeft)  p.horizontalVelocity -= p.airAcceleration;

        if (!p.pressingRight && !p.pressingLeft)
            p.horizontalVelocity *= (1.f - p.airFriction);

        p.position.x += p.horizontalVelocity;

        p.verticalVelocity += p.gravity;
        p.position.y += p.verticalVelocity;
        p.body.setPosition(p.position);

 
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
        p.body.setTexture(p.FallRTex);
        p.currentFrame = 0;
    }

    void update(Player& p) override
    {
        p.animate(2, 238, 298, true);

        if (p.pressingRight) p.horizontalVelocity += p.airAcceleration;
        if (p.pressingLeft)  p.horizontalVelocity -= p.airAcceleration;

        if (!p.pressingRight && !p.pressingLeft)
            p.horizontalVelocity *= (1.f - p.airFriction);

        p.position.x += p.horizontalVelocity;


        p.verticalVelocity += p.gravity;
        p.position.y += p.verticalVelocity;
        p.body.setPosition(p.position);

        // Landing check
        if (p.position.y >= p.groundY)
        {
            p.position.y = p.groundY;
            p.body.setPosition(p.position);

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
        p.body.setTexture(p.LandRTex);
        p.currentFrame = 0;
    }

    void update(Player& p) override
    {
        if (p.animate(2, 238, 298, false))
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
            p.body.setPosition(p.position);

            if (!p.pressingRight)
            {
                p.changeState(p.crouchIdle);
            }
        }
        else
        {
            p.body.setTexture(p.cWalkLTex);
            p.position.x -= p.speed;
            p.body.setPosition(p.position);

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
        p.body.setTexture(p.idleToWalkTex);
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