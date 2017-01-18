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

		void addEntity(Entity e, std::vector<Fields::Ids> f, size_t i);

		void scheduleToSpawn(Entity e, std::vector<Fields::Ids> f);
		void scheduleToDespawn(size_t i);

		Entity* entities;

		std::array<Field*, Fields::Ids::META_FIELD_COUNT> fields;

	private:
		void checkScheduledToSpawn();
		void checkScheduledToDespawn();

		std::vector<std::pair<Entity, std::vector<Fields::Ids>>> scheduledToSpawn;
		std::vector<size_t> scheduledToDespawn;

		static const size_t MAX_ENTITIES = 100;
		std::array<bool, MAX_ENTITIES> currentEntities;
};