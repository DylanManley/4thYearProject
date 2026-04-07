#include <SFML/Graphics.hpp>
#include "Entity.h"

enum class AI_STATE {
	PATROL,
	CHASE,
    ATTACK,
};

class Enemy : public  Entity
{
public:
	void update(Entity& player);
	virtual void loadMovementTextures() override;
	virtual void loadCombatTextures()override;

private:
	AI_STATE aiState = AI_STATE::PATROL;
	sf::Clock patrolClock;
	bool clockRunning = false;

    sf::Clock blockCooldown;
    bool canBlock = true;
    sf::Clock attackCooldown;
    bool canAttack = true;

    //sensors
    bool wallAhead = false;
    bool floorAhead = true;
    bool ceilingAhead = false;
    bool halfAhead = false;

    void updateSensors(Direction facingdir);

    virtual void checkWallAhead() override 
    {
        wallAhead = true;
    }

    virtual void checkFloor() override
    {
        floorAhead = true;
    }

    virtual void checkHalf() override
    {
        halfAhead = true;
    }

    virtual void checkCeiling() override
    {
        ceilingAhead = true;
    }

    bool canStand = false;

    // Membership functions
    float mClose(float dist);
    float mFar(float dist);
    float mPlayerAttacking(bool playerAttacking);
    float mMedium(float dist);

    // Fuzzy rules
    float fuzzyAttack(float dist);
    float fuzzyBlock(float dist, bool playerAttacking);
    float fuzzyDropkick(float dist);
    float fuzzyCloseGap(float dist);

    // Defuzzification
    void applyFuzzyResult(const Entity& player);
};

