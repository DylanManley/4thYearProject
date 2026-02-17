#include <SFML/Graphics.hpp>

class Enemy
{
public:
	sf::RectangleShape collider;

	void setup(sf::Vector2f position, int health);
	void takeDamage(int damage);
	void update();
	void render(sf::RenderWindow& window, bool showDeug);

private:
	int health = 20;
	bool dead = false;
	bool canTakeDamage = true;
	sf::Clock damageClock;
};

