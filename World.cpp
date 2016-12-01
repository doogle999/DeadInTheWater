#include "World.h"

#include "Collisions.h"

#include "IncrementPosition.h"
#include "RenderCircle.h"
#include "KeyboardVelocity.h"

#define REGISTER_FIELD(FIELD) FIELD ## * FIELD ## _TEMP = new FIELD; fields.push_back(FIELD ## _TEMP); fieldNames.push_back(#FIELD); 
#define REGISTER_FIELD_BEHAVIOR(BEHAVIOR, FIELD) behaviors.push_back(new BEHAVIOR(* ## FIELD ## _TEMP)); behaviorNames.push_back(#BEHAVIOR);
#define REGISTER_BEHAVIOR(BEHAVIOR) behaviors.push_back(new BEHAVIOR); behaviorNames.push_back(#BEHAVIOR);

World::World()
{
	entities = (Entity*)calloc(MAX_ENTITIES, sizeof(Entity));
}
World::World(World& w)
{
	entities = (Entity*)malloc(MAX_ENTITIES * sizeof(Entity));
	std::memcpy(entities, w.entities, MAX_ENTITIES * sizeof(Entity));

	fieldEntities = w.fieldEntities;
}

World::~World()
{
	free(entities);
}

World& World::operator=(World other)
{
	swap(*this, other);

	return *this;
}

void World::registerFields()
{
	REGISTER_FIELD(Collisions)
	REGISTER_FIELD_BEHAVIOR(Collisions::StopOnCollision, Collisions)
}
void World::registerBehaviors()
{
	REGISTER_BEHAVIOR(IncrementPosition);
	REGISTER_BEHAVIOR(RenderCircle);
	REGISTER_BEHAVIOR(KeyboardVelocity);
}

void World::input()
{
	for(unsigned int i = 0; i < fields.size(); i++)
	{
		std::vector<Entity*> e; 
		e.reserve(fieldEntities.at(fields[i]).size());
		for(unsigned int j = 0; j < fieldEntities.at(fields[i]).size(); j++)
		{
			e.push_back(&entities[fieldEntities.at(fields[i])[j]]);
		}

		fields[i]->initialize(e);
	}

	for(unsigned int i = 0; i < MAX_ENTITIES; i++)
	{
		entities[i].input();
	}
}
void World::update()
{
	for(unsigned int i = 0; i < MAX_ENTITIES; i++)
	{
		entities[i].update();
	}
}
void World::render()
{
	for(unsigned int i = 0; i < MAX_ENTITIES; i++)
	{
		entities[i].render();
	}
}

void World::addEntity(Entity e)
{
	entities[currentEntities] = e;
	currentEntities += 1;
}
void World::removeEntity(size_t i)
{
	currentEntities -= 1;
	swap(entities[i], entities[currentEntities]);
}

std::vector<Field*> World::fields;
std::vector<std::string> World::fieldNames;
std::vector<Behavior*> World::behaviors;
std::vector<std::string> World::behaviorNames;

#undef REGISTER_FIELD
#undef REGISTER_FIELD_BEHAVIOR
#undef REGISTER_BEHAVIOR