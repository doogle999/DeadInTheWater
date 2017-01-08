#pragma once

#include <vector>
#include <utility>
#include <algorithm>

#include "Entity.h"
#include "EntityFactory.h"
#include "Field.h"
#include "Fields.h"
#include "Behavior.h"
#include "Behaviors.h"
#include "Game.h"

class Entity;
class EntityFactory;
class Field;
class Behavior;
class Game;

class World
{
	public:
		World();
		World(World& w);

		~World();

		World& operator=(World other);

		friend void swap(World& first, World& second)
		{
			using std::swap;

			swap(first.entities, second.entities);
			swap(first.fieldEntities, second.fieldEntities);
			swap(first.currentEntityCount, second.currentEntityCount);
		}

		void input();
		void update();
		void render();

	private:
		void addEntity(Entity e);
		void removeEntity(size_t i);

		static const size_t MAX_ENTITIES = 100;
		size_t currentEntityCount;
		Entity* entities;

		std::map<Field*, std::vector<size_t>> fieldEntities;

		std::vector<Field*> fields;
		std::vector<Behavior*> behaviors;

	friend EntityFactory;
	friend Game;
};