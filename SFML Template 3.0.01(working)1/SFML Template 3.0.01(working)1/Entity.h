#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "StateMachine.h"

enum class Direction {
    LEFT,
    RIGHT
};

class Entity
{
public:
    Entity() = default;

    sf::RectangleShape healthBarBg;
    sf::RectangleShape healthBar;

    virtual void loadMovementTextures();
    virtual void loadCombatTextures();
    virtual void setStates();
    virtual void setUp(sf::Vector2f t_position);
    virtual void takeDamage(int t_damage);
    virtual void checkWallAhead() {}
    virtual void checkFloor() {}
    virtual void checkHalf() {}
    virtual void checkCeiling() {}

    virtual bool animate(int frameCount, int frameWidth, int frameHeight, bool loop = true);
    virtual void changeState(StateMachine* newState);

    Direction facing = Direction::RIGHT;

    bool crouching = false;
    bool isJumping = false;
    bool running = false;
    bool pressingRight = false;
    bool pressingLeft = false;
    bool justJumped = false;
    bool isGrounded = false;
    bool attacking = false;
    bool blocking = false;
    bool canTakeDamage = true;
    virtual void Render(sf::RenderWindow& m_window, bool mapView);

    //movement states
    StateMachine* idle;
    StateMachine* walk;
    StateMachine* run;
    StateMachine* jumping;
    StateMachine* falling;
    StateMachine* landing;
    StateMachine* crouchIdle;
    StateMachine* crouchWalk;
    StateMachine* slide;
    StateMachine* wallSlide;
    StateMachine* wallJump;

    //transition states
    StateMachine* idleToWalk;
    StateMachine* idleToCrouch;
    StateMachine* crouchToIdle;
    StateMachine* idleToJump;
    StateMachine* RunToSlide;
    StateMachine* SlideToRun;
    StateMachine* wallSlideStart;
    StateMachine* wallSlideEnd;
    StateMachine* climb;

    //Combat States
    StateMachine* punch;
    StateMachine* dropKick;
    StateMachine* damageState;
    StateMachine* dead;
    StateMachine* block;

    StateMachine* currentState;

    //Movement Textures
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

    sf::Texture WallSlideStartLTex;
    sf::Texture WallSlideStartRTex;
    sf::Texture wallSlideLTex;
    sf::Texture wallSlideRTex;
    sf::Texture WallSlideLEndTex;
    sf::Texture wallSlideREndTex;
    sf::Texture wallJumpLTex;
    sf::Texture wallJumpRTex;
    sf::Texture climbLTex;
    sf::Texture climbRTex;

    //Combat Textures
    sf::Texture punchRTex;
    sf::Texture punchLTex;
    sf::Texture dropKickLTex;
    sf::Texture dropKickRTex;
    sf::Texture deathLTex;
    sf::Texture deathRTex;
    sf::Texture dmgLTex;
    sf::Texture dmgRTex;
    sf::Texture blockLTex;
    sf::Texture blockRTex;

    sf::Sprite body{ idleLeftTex };
    sf::RectangleShape collider;
    sf::RectangleShape headSensor;

    sf::RectangleShape wallAheadSensor;
    sf::RectangleShape floorAheadSensor;
    sf::RectangleShape ceilingAheadSensor;
    sf::RectangleShape halfAheadSensor;


    int currentFrame = 0;
    sf::Vector2f position;
    int speed = 3;

    float timer = 0.0f;
    float frameTime = 0.06f;
    bool animationFinished = false;

    sf::Clock clock;
    int fallTimer = 0;
    int fatalFall = 90;

    float verticalVelocity = 0.f;
    float gravity = 0.5f;
    float jumpStrength = -12.f;

    float horizontalVelocity = 0.f;
    float airAcceleration = 0.2f;
    float airFriction = 0.05f;

    float slideVelocity;
    float slideDeceleration = 0.1f;

    //combat
    int health = 100;
    int damage = 5;
    sf::RectangleShape hitSensor;
    bool isDead = false;

    sf::Clock damageClock;
};