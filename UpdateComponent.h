#pragma once

#include "Entity.h"

class Entity;

class UpdateComponent
{
	public:
		virtual void update(Entity& e, double t) = 0;
};

