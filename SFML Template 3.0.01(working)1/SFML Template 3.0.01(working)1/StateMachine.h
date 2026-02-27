#pragma once

class Entity;

class StateMachine
{
public:
    virtual ~StateMachine() = default;

    virtual void enter(Entity& e) = 0;
    virtual void update(Entity& e) = 0;
};