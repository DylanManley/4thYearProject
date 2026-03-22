#include <SFML/Graphics.hpp>
#include "Entity.h"

enum class AI_STATE {
	PATROL,
	CHASE,
};

class Enemy : public  Entity
{
public:
	void update(Entity& player);

private:
	AI_STATE aiState = AI_STATE::PATROL;
};

