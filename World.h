#pragma once

#include <vector>
#include <utility>
#include <algorithm>

#include "Entity.h"
#include "EntityFactory.h"
#include "Field.h"
#include "Fields.h"
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
			swap(first.fields, second.fields);
		}

		void input();
		void update();
		void render();

	private:
		void addEntity(Entity e, unsigned int i);

		void checkScheduledToSpawn();
		void checkScheduledForDeletion();

		static const size_t MAX_ENTITIES = 100;
		Entity* entities;

		std::vector<Field*> fields;

	friend EntityFactory;
	friend Game;
};