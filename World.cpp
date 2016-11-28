#include "World.h"

#include "Collisions.h"

#include "IncrementPosition.h"
#include "RenderCircle.h"

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
}

void World::input()
{
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

std::vector<Field*> World::fields;
std::vector<std::string> World::fieldNames;
std::vector<Behavior*> World::behaviors;
std::vector<std::string> World::behaviorNames;

#undef REGISTER_FIELD
#undef REGISTER_FIELD_BEHAVIOR