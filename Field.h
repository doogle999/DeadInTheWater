#pragma once

#include <vector>

#include "World.h"
#include "Entity.h"
#include "Attribute.h"
#include "Attributes.h"
#include "Fields.h"

class World;

class Field
{
	public:
		void setWorld(World* w);

		void addEntityIndex(size_t i);
		void noRepeatAddEntityIndex(size_t i); // Checks if the index is already there before adding, nothing special
		virtual void removeEntityIndex(size_t i); // Removes the entity if it is in this field

		virtual void input();
		virtual void update();
		virtual void render();

		virtual std::vector<Attribute::Ids> getNecessaryProperties() = 0;
		bool compatible(Entity* e);

	protected:
		std::vector<size_t> ei;
		World* w;
};