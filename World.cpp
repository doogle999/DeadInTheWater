#include "World.h"

#include "Collisions.h"
#include "Selectables.h"
#include "Gravity.h"
#include "Camera2D.h"

#include "IncrementPosition.h"
#include "IncrementVelocity.h"
#include "RenderCircle.h"
#include "KeyboardVelocity.h"
#include "KillIfNotMoving.h"

#define ADD_FIELD(FIELD) FIELD* TEMP_ ## FIELD = new FIELD; fields[Fields::Ids::Id_ ## FIELD] = TEMP_ ## FIELD;
#define ADD_FIELD_BEHAVIOR(BEHAVIOR, FIELD) behaviors[Behaviors::Ids::Id_ ## FIELD ## ___ ## BEHAVIOR] = new FIELD ## :: ## BEHAVIOR(*TEMP_ ## FIELD);
#define ADD_BEHAVIOR(BEHAVIOR) behaviors[Behaviors::Ids::Id_ ## BEHAVIOR] = new BEHAVIOR;

World::World()
{
	fields.resize(Fields::Ids::META_FIELD_COUNT);
	behaviors.resize(Behaviors::Ids::META_BEHAVIOR_COUNT);

	ADD_FIELD(Selectables)

	ADD_FIELD(Collisions)
	ADD_FIELD_BEHAVIOR(StopOnCollision, Collisions)

	ADD_FIELD(Gravity)

	ADD_FIELD(Camera2D)
	ADD_FIELD_BEHAVIOR(RenderCircle, Camera2D)

	ADD_BEHAVIOR(IncrementPosition)
	ADD_BEHAVIOR(IncrementVelocity)
	ADD_BEHAVIOR(KillIfNotMoving)
	ADD_BEHAVIOR(KeyboardVelocity)
	ADD_BEHAVIOR(RenderCircle)

	entities = (Entity*)calloc(MAX_ENTITIES, sizeof(Entity));
}
World::World(World& w)
{
	entities = (Entity*)malloc(MAX_ENTITIES * sizeof(Entity));
	std::memcpy(entities, w.entities, MAX_ENTITIES * sizeof(Entity));

	fields = w.fields;
	behaviors = w.behaviors;

	currentEntityCount = w.currentEntityCount;
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

void World::input()
{
	bool noEntitiesSpawned = true;

	std::vector<size_t> removedEntities;
	for(unsigned int i = 0; i < currentEntityCount; i++)
	{
		for(unsigned int j = 0; j < entities[i].scheduledToSpawn.size(); j++)
		{
			addEntity(entities[i].scheduledToSpawn[j]);
			noEntitiesSpawned = false;
		}

		if(entities[i].scheduledForDeletion)
		{
			removedEntities.push_back(i);
		}
	}

	for(int i = removedEntities.size() - 1; i >= 0; i--)
	{
		removeEntity(removedEntities[i]);
	}

	for(unsigned int i = 0; i < fields.size(); i++)
	{
		fields[i]->input();
	}

	for(unsigned int i = 0; i < currentEntityCount; i++)
	{
		entities[i].input();
	}
}
void World::update()
{
	for(unsigned int i = 0; i < fields.size(); i++)
	{
		fields[i]->update();
	}
	for(unsigned int i = 0; i < currentEntityCount; i++)
	{
		entities[i].update();
	}
}
void World::render()
{
	for(unsigned int i = 0; i < fields.size(); i++)
	{
		fields[i]->render();
	}
	for(unsigned int i = 0; i < currentEntityCount; i++)
	{
		entities[i].render();
	}
}

void World::addEntity(Entity e)
{
	entities[currentEntityCount] = e;
	currentEntityCount += 1;
}
void World::removeEntity(size_t i)
{
	currentEntityCount -= 1;
	swap(entities[i], entities[currentEntityCount]);

	for(unsigned int j = 0; j < fields.size(); j++)
	{
		std::vector<Entity*>* fieldEntitiesPointer = &fields[j]->entities;

		if(fieldEntitiesPointer->size() > 0)
		{
			size_t hasI = -1;
			size_t nextGreaterThanI = (fieldEntitiesPointer->back() - entities) / sizeof(Entity);
			bool hasCurrentEntities = false;

			for(unsigned int k = 0; k < fieldEntitiesPointer->size(); k++)
			{
				if((fieldEntitiesPointer->at(k) - entities) / sizeof(Entity) == i)
				{
					hasI = k;
				}
				else if((fieldEntitiesPointer->at(k) - entities) / sizeof(Entity) > i)
				{
					nextGreaterThanI = k;
				}
				else if((fieldEntitiesPointer->at(k) - entities) / sizeof(Entity) == currentEntityCount)
				{
					hasCurrentEntities = true;
				}
			}

			if(hasI != -1 && hasCurrentEntities)
			{
				fieldEntitiesPointer->pop_back();
			}
			else if(hasI != -1 && !hasCurrentEntities)
			{
				fieldEntitiesPointer->erase(fieldEntitiesPointer->begin() + nextGreaterThanI);
			}
			else if(hasI == -1 && hasCurrentEntities)
			{
				fieldEntitiesPointer->insert(fieldEntitiesPointer->begin() + nextGreaterThanI, &entities[i]);
				fieldEntitiesPointer->pop_back();
			}
		}
	}
}

#undef REGISTER_FIELD
#undef REGISTER_FIELD_BEHAVIOR
#undef REGISTER_BEHAVIOR