#pragma once

#include <array>
#include <utility>
#include <algorithm>

#include "Entity.h"
#include "Field.h"
#include "Fields.h"
#include "Game.h"

class Entity;
class Field;

class World
{
	public:
		World();
		World(World& w);

		~World();

		World& operator=(World other);

		void input();
		void update();
		void render();

		Entity* entities;
		std::array<Field*, Fields::Ids::META_FIELD_COUNT> fields;

		void addEntity(Entity e, unsigned int i);

	private:
		void checkScheduledToSpawn();
		void checkScheduledForDeletion();

		static const size_t MAX_ENTITIES = 100;
};