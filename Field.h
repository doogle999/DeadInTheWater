#pragma once

#include <vector>

#include "World.h"
#include "Entity.h"
#include "Properties.h"
#include "Fields.h"

class World;
class Entity;

class Field
{
	public:
		void setWorld(World* w);


		virtual void input();
		virtual void update();
		virtual void render();

		virtual std::vector<P::Ids> getNecessaryProperties() = 0;

	protected:
		std::vector<size_t> ei;
		World* w;

	friend World;
};