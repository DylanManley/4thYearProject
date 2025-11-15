#pragma once
class Player;

class StateMachine
{
public:
    virtual ~StateMachine() = default;

    virtual void enter(Player& p) = 0;
    virtual void update(Player& p) = 0;
};