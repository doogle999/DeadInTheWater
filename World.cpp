#include "World.h"

#include "Collisions.h"
#include "Selectables.h"
#include "Gravity.h"
#include "Camera2D.h"

#define ADD_FIELD(FIELD) FIELD* TEMP_ ## FIELD = new FIELD; fields[Fields::Ids::Id_ ## FIELD] = TEMP_ ## FIELD; fields[Fields::Ids::Id_ ## FIELD]->setWorld(this);

World::World()
{
	fields.resize(Fields::Ids::META_FIELD_COUNT);

	// For now, the order these are in is their call order, will add a priority system at some point
	ADD_FIELD(Selectables)
	ADD_FIELD(Collisions)
	ADD_FIELD(Gravity)
	ADD_FIELD(Camera2D)

	entities = (Entity*)calloc(MAX_ENTITIES, sizeof(Entity));
}
World::World(World& w)
{
	entities = (Entity*)malloc(MAX_ENTITIES * sizeof(Entity));
	std::memcpy(entities, w.entities, MAX_ENTITIES * sizeof(Entity));

	fields = w.fields;
	for(unsigned int i = 0; i < fields.size(); i++)
	{
		fields[i]->setWorld(this);
	}
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
	checkScheduledToSpawn();
	checkScheduledForDeletion();

	for(unsigned int i = 0; i < fields.size(); i++)
	{
		fields[i]->input();
	}
}
void World::update()
{
	for(unsigned int i = 0; i < fields.size(); i++)
	{
		fields[i]->update();
	}
}
void World::render()
{
	for(unsigned int i = 0; i < fields.size(); i++)
	{
		fields[i]->render();
	}
}

void World::addEntity(Entity e, unsigned int i)
{
	if(i < MAX_ENTITIES)
	{
		entities[i] = e;
		for(unsigned int j = 0; j < entities[i].fields.size(); j++)
		{
			if(entities[i].compatible(fields[entities[i].fields[j]]))
			{
				fields[entities[i].fields[j]]->ei.push_back(i);
			}
			else
			{
				printf("Tried to add an entity to a field, but it wasn't compatible \n");
			}
		}
	}
	else
	{
		printf("Tried to add an entity, but the world is full (exceeded MAX_ENTITIES), the entity was not added \n");
	}
}

void World::checkScheduledToSpawn()
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
						addEntity(entities[i].scheduledToSpawn[j], entitiesIndex - 1);
						break;
					}
				}
			}
			entities[i].scheduledToSpawn.clear();
		}
	}
}
void World::checkScheduledForDeletion()
{
	for(unsigned int i = 0; i < MAX_ENTITIES; i++)
	{
		if(entities[i].scheduledForDeletion)
		{
			entities[i].deleted = true;
			entities[i].scheduledForDeletion = false;
		}
	}
}

#undef REGISTER_FIELD
#undef REGISTER_FIELD_BEHAVIOR
#undef REGISTER_BEHAVIOR