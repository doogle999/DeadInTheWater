#pragma once

#include <vector>
#include <utility>
#include <algorithm>

#include "Entity.h"
#include "EntityFactory.h"
#include "Field.h"
#include "Behavior.h"
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
		}

		static void registerFields();
		static void registerBehaviors();

		void input();
		void update();
		void render();

	private:
		void addEntity(Entity e);
		void removeEntity(size_t i);

		static const size_t MAX_ENTITIES = 100;
		size_t currentEntities;
		Entity* entities;

		std::map<Field*, std::vector<size_t>> fieldEntities;

		static std::vector<Field*> fields;
		static std::vector<std::string> fieldNames;
		static std::vector<Behavior*> behaviors;
		static std::vector<std::string> behaviorNames;

	friend EntityFactory;
	friend Game;
};