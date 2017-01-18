#pragma once

#include <vector>
#include <cassert>
#include <utility>

#include "Properties.h"
#include "Field.h"
#include "Fields.h"
#include "EntityFactory.h"

class EntityFactory;
class Field;
struct Fields;

// ACCESS PROPERTIES WITH THIS MACRO TO ENSURE THE TYPE IS CORRECT
// AXS stands for Access (aka AXESS aka AXS), use to access an entity's property 
#define AXS(NAME) access<P::TYPE_ ## NAME>(P::Ids:: ## NAME)

class Entity
{
	public:	
		Entity();
		Entity(const Entity& e);
		Entity(std::vector<P::Ids> p);

		~Entity();

		Entity& operator=(Entity other);

		friend void swap(Entity& first, Entity& second)
		{
			using std::swap;

			swap(first.properties, second.properties);
			swap(first.propertiesMapLength, second.propertiesMapLength);
			swap(first.propertiesMap, second.propertiesMap);
		}

		template <typename T>
		T& access(P::Ids id);

		bool compatible(Field* f);

	private:
		void* properties;
		int* propertiesMapLength;
		std::pair<P::Ids, size_t>* propertiesMap;

	friend EntityFactory;
};

template<typename T>
T& Entity::access(P::Ids id) // When called you need to pass the right type, if the property you want is an int but you call double you get undefined behavior
{
	for(int i = 0; i < *propertiesMapLength; i++) // Search through the properties map to find the property we want
	{
		if((propertiesMap + i)->first == id)
		{
			return *reinterpret_cast<T*>(static_cast<char*>(properties) + propertiesMap[i].second); // Return the value of the property at the location
		}
	}
	assert(0 && "Attempted to access a property that either does not exist or this entity does not have"); // The property that was being accessed was not in the map
}