#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <cassert>

#include "World.h"
#include "Behavior.h"
#include "Field.h"
#include "Entity.h"
#include "Properties.h"

#include "tinyxml2.h"

class World;

class EntityFactory
{
	public:
		EntityFactory();

		~EntityFactory();

		World createWorld(std::string path); // Creates a world, terminates if it can't parse the XML

		Entity createEntity(tinyxml2::XMLElement* entityXMLElement, Entity* location); // Creates and returns an Entity based on an XMLElement, terminates the program if it can't parse the XML

		template<typename T>
		T interpretPropertyValue(tinyxml2::XMLElement* value); // Interprets an XML element that holds the value of a property and converts it into the specified type 

		template<> int interpretPropertyValue<int>(tinyxml2::XMLElement* value);
		template<> double interpretPropertyValue<double>(tinyxml2::XMLElement* value);
};