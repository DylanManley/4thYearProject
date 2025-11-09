#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

enum class MovementState
{
    IDLE,
    WALK_RIGHT,
    WALK_LEFT,
    JUMPING,
    CROUCH_IDLE,
    CROUCH_WALK_RIGHT,
    CROUCH_WALK_LEFT,

    //transition states
    IDLE_TO_WALK,
    IDLE_TO_CROUCH,
    CROUCH_TO_IDLE
};

class Player
{
public:
    Player() = default;

    void setUp();
    void update();

    sf::Texture idleTexture;
    sf::Texture idleToWalkTexture;
    sf::Texture walkRightTexture;
    sf::Texture walkLeftTexture;
    sf::Texture crouchDownTexture;
    sf::Texture standUpTexture;
    sf::Texture CrouchWalkRight;
    sf::Texture CrouchWalkLeft;
    sf::Sprite body{ idleTexture };

private:
    int currentFrame = 0;
    float timer = 0.0f;
    float frameTime = 0.06f; 
    bool animationFinished = false;
    bool crouching = false;

    sf::Clock clock;
    sf::Vector2f position;
    int speed = 3;
    MovementState currentState = MovementState::IDLE;

    bool animate(int frameCount, int frameWidth, int frameHeight, bool loop = true);
};
