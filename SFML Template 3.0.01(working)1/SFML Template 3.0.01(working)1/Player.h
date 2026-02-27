#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Entity.h"

class Player : public Entity
{
public:
	void update() override;
};
