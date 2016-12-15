#pragma once

#include "Entity.h"
#include "Properties.h"
#include "Game.h"

class Entity;

class Behavior
{
	public:
		virtual void run(Entity& e) = 0;

		virtual std::vector<P::Ids> getNecessaryProperties() = 0;
};
