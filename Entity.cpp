#include "Entity.h"

#define ADD_ATTRIBUTE_CONSTRUCTOR_CASE(NAME) case Attribute::Ids:: ## NAME: { attributes[Attribute::Ids:: ## NAME] = new A:: ## NAME(); break; }
#define ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(NAME) case Attribute::Ids:: ## NAME: { attributes[Attribute::Ids:: ## NAME] = new A:: ## NAME(dynamic_cast<A:: ## NAME ## &>(*e.attributes[a[i]])); break; }

Entity::Entity()
{
	for(unsigned int i = 0; i < attributes.size(); i++)
	{
		attributes[i] = nullptr;
	}
};
Entity::Entity(const Entity& e) 
{
	std::vector<Attribute::Ids> a = e.getAttributeIds();

	for(unsigned int i = 0; i < attributes.size(); i++)
	{
		attributes[i] = nullptr;
	}

	for(unsigned int i = 0; i < a.size(); i++)
	{
		switch(a[i])
		{
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(Translation)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(TimeoutTime)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(ReloadTime)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(HitPolygon)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(Orientation)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(IslandTriangles)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(ShipMovement)

			default: assert(0 && "Missing Attribute copy constructor case in Entity copy constructor");
		}
	}
}
Entity::Entity(std::vector<Attribute::Ids> a)
{
	for(unsigned int i = 0; i < attributes.size(); i++)
	{
		attributes[i] = nullptr;
	}

	for(unsigned int i = 0; i < a.size(); i++)
	{
		switch(a[i])
		{
			ADD_ATTRIBUTE_CONSTRUCTOR_CASE(Translation)
			ADD_ATTRIBUTE_CONSTRUCTOR_CASE(TimeoutTime)
			ADD_ATTRIBUTE_CONSTRUCTOR_CASE(ReloadTime)
			ADD_ATTRIBUTE_CONSTRUCTOR_CASE(HitPolygon)
			ADD_ATTRIBUTE_CONSTRUCTOR_CASE(Orientation)
			ADD_ATTRIBUTE_CONSTRUCTOR_CASE(IslandTriangles)
			ADD_ATTRIBUTE_CONSTRUCTOR_CASE(ShipMovement)

			default: assert(0 && "Missing Attribute constructor case in Entity constructor");
		}
	}
}

Entity::~Entity()
{
	for(unsigned int i = 0; i < attributes.size(); i++)
	{
		delete attributes[i];
	}
}

std::vector<Attribute::Ids> Entity::getAttributeIds() const
{
	std::vector<Attribute::Ids> a;

	for(unsigned int i = 0; i < attributes.size(); i++)
	{
		if(attributes[i] != nullptr)
		{
			a.push_back(static_cast<Attribute::Ids>(i));
		}
	}

	return a;
}

Entity& Entity::operator=(const Entity& e)
{
	for(unsigned int i = 0; i < attributes.size(); i++)
	{
		delete attributes[i];
		attributes[i] = nullptr;
	}

	std::vector<Attribute::Ids> a = e.getAttributeIds();

	for(unsigned int i = 0; i < a.size(); i++)
	{
		switch(a[i])
		{
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(Translation)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(TimeoutTime)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(ReloadTime)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(HitPolygon)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(Orientation)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(IslandTriangles)
			ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE(ShipMovement)

			default: assert(0 && "Missing Attribute copy constructor case in Entity assignment operator");
		}
	}

	return *this;
}

bool Entity::hasAttribute(Attribute::Ids a)
{
	bool returnVal;

	try
	{
		returnVal = attributes.at(a) != nullptr;
	}
	catch(std::out_of_range)
	{
		returnVal = false;
	}
	return returnVal;
}

#undef ADD_ATTRIBUTE_CONSTRUCTOR_CASE
#undef ADD_ATTRIBUTE_COPY_CONSTRUCTOR_CASE