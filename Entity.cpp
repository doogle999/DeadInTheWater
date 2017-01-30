#include "Entity.h"

Entity::Entity() 
{
	properties = nullptr; 
	propertiesMapLength = nullptr;
	propertiesMap = nullptr; 
};
Entity::Entity(const Entity& e) // Copy constructor (deep)
{
	if(e.properties == nullptr || e.propertiesMap == nullptr || e.propertiesMapLength == nullptr)
	{
		properties = nullptr;
		propertiesMapLength = nullptr;
		propertiesMap = nullptr;
	}
	else
	{
		size_t propertiesSize = reinterpret_cast<char*>(e.propertiesMapLength) - static_cast<char*>(e.properties); // Size of the properties 
		size_t totalSize = reinterpret_cast<char*>(e.propertiesMap + *(e.propertiesMapLength)) - static_cast<char*>(e.properties); // Size of the properties, the propertiesMap, and its length

		properties = malloc(totalSize); // Allocate the memory for all three
		propertiesMapLength = reinterpret_cast<unsigned int*>(static_cast<char*>(properties) + propertiesSize); // Set the location of the propertiesMap length
		propertiesMap = reinterpret_cast<std::pair<P::Ids, size_t>*>(static_cast<char*>(properties) + propertiesSize + sizeof(unsigned int)); // Set the location of the propertiesMap

		std::memcpy(properties, e.properties, totalSize); // Copy the bytes from one Entity to another
	}
}
Entity::Entity(std::vector<P::Ids> p)
{
	std::vector<std::pair<P::Ids, size_t>> propertiesMapTemporary; // Stores the id and memory location after void* properties
	propertiesMapTemporary.reserve(p.size());

	size_t size = 0; // Amount of memory used for properties
	for(unsigned int i = 0; i < p.size(); i++)
	{
		propertiesMapTemporary.push_back({ p[i], size }); // Since size is the size of all the memory up to this point, it's also the memory location after void* properties for a property p[i]
		size += P::Sizes.at(p[i]); // Increment size by the size of the type of the property
	}

	properties = malloc(size + sizeof(int) + sizeof(std::pair<P::Ids, size_t>) * propertiesMapTemporary.size()); // Allocate a big chunk of memory for properties, a property map, and a property map length

	propertiesMapLength = reinterpret_cast<unsigned int*>(static_cast<char*>(properties) + size); // Start the properties map length after the end of the properties
	*propertiesMapLength = propertiesMapTemporary.size(); // Give properties map length an actual value, which is the amount of properties passed

	propertiesMap = reinterpret_cast<std::pair<P::Ids, size_t>*>(static_cast<char*>(properties) + size + sizeof(unsigned int)); // Start the properties map after the end of properties map length
	for(unsigned int i = 0; i < propertiesMapTemporary.size(); i++) // Set each element of properties map to the temporary properties map
	{
		*(propertiesMap + i) = propertiesMapTemporary[i];
	}
}

Entity::~Entity()
{
	free(properties); // Properties is what we malloced so we free properties, nothing else
}

Entity& Entity::operator=(Entity other)
{
	swap(*this, other);

	return *this;
}

bool Entity::hasProperty(P::Ids id)
{
	for(unsigned int i = 0; i < *propertiesMapLength; i++)
	{
		if((propertiesMap + i)->first == id)
		{
			return true;
		}
	}
	return false;
}