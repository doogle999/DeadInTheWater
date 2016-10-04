#pragma once

#include "Entity.h"

class Entity;

class RenderComponent
{
	public:
		virtual void render(Entity& e) = 0;
};

