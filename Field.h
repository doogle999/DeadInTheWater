#pragma once

#include <vector>

#include "Entity.h"
#include "Properties.h"

class Entity;

class Field
{
	public:
		virtual void input();
		virtual void update();
		virtual void render();

		virtual std::vector<P::Ids> getNecessaryProperties() = 0;

		std::vector<Entity*> entities;
};