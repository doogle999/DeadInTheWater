#pragma once

#include <array>
#include <utility>
#include <tuple>
#include <algorithm>

#include "Entity.h"
#include "Field.h"
#include "Fields.h"
#include "Game.h"

class Field;

class World
{
	public:
		World();
		World(World& w);

		~World();

		World& operator=(World w);

		bool input();
		void update();
		void render();

		void scheduleToSpawn(Entity e, std::vector<Fields::Ids> f);
		void scheduleToDespawn(size_t i);

		void scheduleToChangeFields(size_t i, Fields::Ids f, bool b);

		void scheduleToClose();

		static const size_t MAX_ENTITIES = 100;
		std::array<Entity, MAX_ENTITIES> entities;

		std::array<Field*, Fields::Ids::META_FIELD_COUNT> fields;

	private:
		void addEntity(Entity e, std::vector<Fields::Ids> f, size_t i);
		
		void checkScheduledToSpawn();
		void checkScheduledToDespawn();

		void checkScheduledToChangeFields();

		std::vector<std::pair<Entity, std::vector<Fields::Ids>>> scheduledToSpawn;
		std::vector<size_t> scheduledToDespawn;

		std::vector<std::tuple<size_t, Fields::Ids, bool>> scheduledToChangeFields; // Index of the entity, field it is changing, whether it is joining (true) or leaving (false)

		bool scheduledToClose;

		std::array<bool, MAX_ENTITIES> currentEntities;
};