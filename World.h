#pragma once

#include <vector>
#include <utility>

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
		}

		static void registerFields();
		static void registerBehaviors();

		void input();
		void update();
		void render();

	private:
		static const size_t MAX_ENTITIES = 100;
		Entity* entities;

		static std::vector<Field*> fields;
		static std::vector<std::string> fieldNames;
		static std::vector<Behavior*> behaviors;
		static std::vector<std::string> behaviorNames;

	friend EntityFactory;
	friend Game;
};