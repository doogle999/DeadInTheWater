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
	for(unsigned int i = 0; i < MAX_ENTITIES; i++)
	{
		for(unsigned int j = 0; j < entities[i].scheduledToSpawn.size(); j++)
		{
			for(unsigned int k = 0; k < MAX_ENTITIES; k++)
			{
				if(entities[k].scheduledForDeletion == true)
				{
					addEntity(entities[i].scheduledToSpawn[j]);
				}
			}
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

	for(unsigned int i = 0; i < MAX_ENTITIES; i++)
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
	for(unsigned int i = 0; i < MAX_ENTITIES; i++)
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
	for(unsigned int i = 0; i < MAX_ENTITIES; i++)
	{
		entities[i].render();
	}
}

void World::addEntities()
{
	size_t entitiesIndex = 0;

	for(unsigned int i = 0; i < MAX_ENTITIES; i++)
	{
		if(!entities[i].scheduledToSpawn.empty())
		{
			for(unsigned int j = 0; j < entities[i].scheduledToSpawn.size(); j++)
			{
				while(entitiesIndex < MAX_ENTITIES)
				{
					entitiesIndex += 1;
					if(entities[entitiesIndex - 1].scheduledForDeletion == true)
					{
						entities[entitiesIndex - 1] = entities[i].scheduledToSpawn[j];
						break;
					}
				}
			}
			entities[i].scheduledToSpawn.clear();
		}
	}
}

#undef REGISTER_FIELD
#undef REGISTER_FIELD_BEHAVIOR
#undef REGISTER_BEHAVIOR