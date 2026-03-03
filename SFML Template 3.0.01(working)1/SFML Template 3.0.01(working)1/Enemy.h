#include <SFML/Graphics.hpp>
#include "Entity.h"

class Enemy : public  Entity
{
public:
	void update() override;
	void takeDamage(int damage);

private:
	bool canTakeDamage = true;
	sf::Clock damageClock;
};

