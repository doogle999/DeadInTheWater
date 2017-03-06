#pragma once

#include <vector>
#include <array>
#include <cassert>
#include <exception>
#include <utility>

#include "Attribute.h"
#include "Attributes.h"

// ACCESS PROPERTIES WITH THIS MACRO TO ENSURE THE TYPE IS CORRECT
// AXS stands for Access (aka AXESS aka AXS), use to access an entity's property 
#define AXS(NAME) access<A:: ## NAME>(Attribute::Ids:: ## NAME)

class Entity
{
	public:	
		Entity();
		Entity(const Entity& e);
		Entity(std::vector<Attribute::Ids> a);

		~Entity();

		std::vector<Attribute::Ids> getAttributeIds() const;

		Entity& operator=(const Entity& e);

		template <typename T>
		T& access(Attribute::Ids);

		bool hasAttribute(Attribute::Ids a);

	private:
		std::array<Attribute*, Attribute::Ids::META_ATTRIBUTE_COUNT> attributes;
};

template<typename T>
T& Entity::access(Attribute::Ids a) // When called you need to pass the right type, if the attribute you want is an int but you call double you get undefined behavior
{
	if(hasAttribute(a))
	{
		return dynamic_cast<T&>(*attributes[a]);
	}
	else
	{
		assert(0 && "Attempted to access an attribute that either does not exist or that this entity does not have");
		abort(); // Get rid of the goddamn warning that prints for every single call to this function that "not all control paths return a value"
	}
}