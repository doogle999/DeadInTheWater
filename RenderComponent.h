#pragma once

#include "SFML\Graphics.hpp"

#include "Entity.h"

class Entity;

class RenderComponent
{
	public:
		virtual void render(Entity& e, sf::RenderWindow* w) = 0;
};

