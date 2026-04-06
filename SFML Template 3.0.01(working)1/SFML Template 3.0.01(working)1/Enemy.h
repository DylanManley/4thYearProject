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

