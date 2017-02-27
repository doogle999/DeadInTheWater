#include "World.h"

#include "Collisions.h"
#include "Selectables.h"
#include "Gravity.h"
#include "Camera2D.h"
#include "RenderBoat.h"
#include "SpawnProjectile.h"
#include "RenderProjectile.h"
#include "Timeout.h"

#define ADD_FIELD(FIELD) FIELD* TEMP_ ## FIELD = new FIELD; fields[Fields::Ids::Id_ ## FIELD] = TEMP_ ## FIELD; fields[Fields::Ids::Id_ ## FIELD]->setWorld(this);

World::World()
{
	for(unsigned int i = 0; i < MAX_ENTITIES; i++)
	{
		currentEntities[i] = false;
	}

	// For now, the order these are in is their call order, will add a priority system at some point
	ADD_FIELD(Selectables)
	ADD_FIELD(Collisions)
	ADD_FIELD(Gravity)
	ADD_FIELD(Camera2D)
	ADD_FIELD(RenderBoat)
	ADD_FIELD(SpawnProjectile)
	ADD_FIELD(RenderProjectile)
	ADD_FIELD(Timeout)
}
World::World(World& w) // Copy constructor (deep)
{
	for(int i = 0; i < MAX_ENTITIES; i++)
	{
		entities[i] = Entity(w.entities[i]);
	}

	fields = w.fields;
	for(unsigned int i = 0; i < fields.size(); i++)
	{
		fields[i]->setWorld(this);
	}

	scheduledToSpawn = w.scheduledToSpawn;
	scheduledToDespawn = w.scheduledToDespawn;
	scheduledToChangeFields = w.scheduledToChangeFields;

	currentEntities = w.currentEntities;
}

World::~World() {}

World& World::operator=(World w)
{
	using std::swap;

	swap(this->entities, w.entities);

	swap(this->fields, w.fields);
	for(unsigned int i = 0; i < this->fields.size(); i++)
	{
		this->fields[i]->setWorld(this);
	}

	swap(this->scheduledToSpawn, w.scheduledToSpawn);
	swap(this->scheduledToDespawn, w.scheduledToDespawn);
	swap(this->scheduledToChangeFields, w.scheduledToChangeFields);

	swap(this->currentEntities, w.currentEntities);

	return *this;
}

void World::input()
{
	checkScheduledToSpawn();
	checkScheduledToDespawn();
	checkScheduledToChangeFields();

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

void World::addEntity(Entity e, std::vector<Fields::Ids> f,  size_t i)
{
	if(i < MAX_ENTITIES)
	{
		entities[i] = e;
		currentEntities[i] = true;
		for(unsigned int j = 0; j < f.size(); j++)
		{
			if(fields[f[j]]->compatible(&entities[i]))
			{
				fields[f[j]]->addEntityIndex(i);
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

void World::scheduleToSpawn(Entity e, std::vector<Fields::Ids> f)
{
	scheduledToSpawn.push_back(std::make_pair(e, f));
}
void World::scheduleToDespawn(size_t i)
{
	scheduledToDespawn.push_back(i);
}

void World::scheduleToChangeFields(size_t i, Fields::Ids f, bool b) // Index of the entity, fields it is changing, 
{
	scheduledToChangeFields.push_back(std::make_tuple(i, f, b));
}

void World::checkScheduledToSpawn() // This is optimized so that it only has to run through the whole entities array checking for free spots once
{
	size_t entitiesIndex = 0;

	for(unsigned int j = 0; j < scheduledToSpawn.size(); j++)
	{
		while(entitiesIndex < MAX_ENTITIES)
		{
			entitiesIndex += 1;
			if(currentEntities[entitiesIndex - 1] == false)
			{
				addEntity(scheduledToSpawn[j].first, scheduledToSpawn[j].second, entitiesIndex - 1);
				break;
			}
		}
	}
	
	scheduledToSpawn.clear();
}
void World::checkScheduledToDespawn()
{
	for(unsigned int i = 0; i < scheduledToDespawn.size(); i++)
	{
		currentEntities[scheduledToDespawn[i]] = false;

		for(unsigned int j = 0; j < fields.size(); j++)
		{
			fields[j]->removeEntityIndex(scheduledToDespawn[i]);
		}
	}

	scheduledToDespawn.clear();
}

void World::checkScheduledToChangeFields()
{
	for(unsigned int i = 0; i < scheduledToChangeFields.size(); i++)
	{
		if(std::get<2>(scheduledToChangeFields[i]) == true)
		{
			if(fields[std::get<1>(scheduledToChangeFields[i])]->compatible(&entities[std::get<0>(scheduledToChangeFields[i])]))
			{
				fields[std::get<1>(scheduledToChangeFields[i])]->noRepeatAddEntityIndex(std::get<0>(scheduledToChangeFields[i]));
			}
		}
		else
		{
			fields[std::get<1>(scheduledToChangeFields[i])]->removeEntityIndex(std::get<0>(scheduledToChangeFields[i]));
		}
	}

	scheduledToChangeFields.clear();
}

#undef REGISTER_FIELD
#undef REGISTER_FIELD_BEHAVIOR
#undef REGISTER_BEHAVIOR