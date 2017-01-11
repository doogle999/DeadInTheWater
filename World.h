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
			swap(first.fields, second.fields);
			swap(first.behaviors, second.behaviors);
			swap(first.currentEntityCount, second.currentEntityCount);
		}

		void input();
		void update();
		void render();

	private:
		void addEntities();
		void removeEntity(size_t i);

		Entity* entities;
		static const size_t MAX_ENTITIES = 100;

		std::vector<Field*> fields;
		std::vector<Behavior*> behaviors;

	friend EntityFactory;
	friend Game;
};