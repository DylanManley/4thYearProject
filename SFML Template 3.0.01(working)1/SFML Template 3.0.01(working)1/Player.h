#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "StateMachine.h"

enum class Direction { 
    LEFT,
    RIGHT 
};

class Player
{
public:
    Player() = default;

    void loadTextures();
    void setStates();
    void setUp();
    void update();

    bool animate(int frameCount, int frameWidth, int frameHeight, bool loop = true);
    void changeState(StateMachine* newState);

    Direction facing = Direction::RIGHT;
    bool pressingRight = false;
    bool pressingLeft = false;
    bool crouching = false;
    bool isJumping = false;
    bool running = false;
    bool justJumped = false;
    bool isGrounded = false;
    void Render(sf::RenderWindow& m_window, bool m_debug);

    StateMachine* idle;
    StateMachine* walk;
    StateMachine* run;
    StateMachine* jumping;
    StateMachine* falling;
    StateMachine* landing;
    StateMachine* crouchIdle;
    StateMachine* crouchWalk;
    StateMachine* slide;

    //transition states
    StateMachine* idleToWalk;
    StateMachine* idleToCrouch;
    StateMachine* crouchToIdle;
    StateMachine* idleToJump; 
    StateMachine* RunToSlide;
    StateMachine* SlideToRun;

    StateMachine* currentState;


    sf::Texture idleRightTex;
    sf::Texture idleLeftTex;
    sf::Texture idleToWalkLTex;
    sf::Texture idleToWalkRTex;
    sf::Texture walkRightTex;
    sf::Texture walkLeftTex;

    sf::Texture crouchDownTex;
    sf::Texture standUpTex;
    sf::Texture crouchTex;
    sf::Texture cWalkRTex;
    sf::Texture cWalkLTex;
    sf::Texture runLeftTex;
    sf::Texture runRightTex;

    sf::Texture slideStartLTex;
    sf::Texture slideStartRTex;
    sf::Texture slideLTex;
    sf::Texture slideRTex;
    sf::Texture slideEndLTex;
    sf::Texture slideEndRTex;


    sf::Texture JumpStartL;
    sf::Texture JumpStartR;
    sf::Texture JumpLTex;
    sf::Texture JumpRTex;
    sf::Texture FallLTex;
    sf::Texture FallRTex;
    sf::Texture LandLTex;
    sf::Texture LandRTex;

    sf::Sprite body{ idleLeftTex };
    sf::RectangleShape collider;
    

    int currentFrame = 0;
    sf::Vector2f position;
    int speed = 3;

    float timer = 0.0f;
    float frameTime = 0.06f; 
    bool animationFinished = false;

    sf::Clock clock;

    float verticalVelocity = 0.f;
    float gravity = 0.5f;
    float jumpStrength = -12.f;

    float horizontalVelocity = 0.f;
    float airAcceleration = 0.2f;
    float airFriction = 0.05f;

};
