#pragma once

#include "SFML/Window.hpp"

#include "Entity.h"

class Entity;

class InputComponent
{
	public:
		virtual void input(Entity& e, sf::Window*) = 0;
};

