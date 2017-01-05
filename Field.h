#pragma once

#include <vector>

#include "Entity.h"
#include "Properties.h"

class Entity;

class Field
{
	public:
		void initialize(std::vector<Entity*> e);

		virtual void input();
		virtual void update();
		virtual void render();

		virtual std::vector<P::Ids> getNecessaryProperties() = 0;

	protected:
		std::vector<Entity*> entities;
};