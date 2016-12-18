#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <exception>

#include "World.h"
#include "Behavior.h"
#include "Field.h"
#include "Entity.h"
#include "Properties.h"

#include "tinyxml2.h"

class World;
class Entity;

class EntityFactory
{
	public:
		static World createWorld(std::string path); // Creates a world, terminates if it can't parse the XML

		static Entity createEntity(tinyxml2::XMLElement* entityElem, World* parentWorld); // Creates and returns an Entity based on an XMLElement, terminates the program if it can't parse the XML

		static Entity createEntityFromProperties(tinyxml2::XMLElement* propertiesElem);
		static Entity createEntityFromProperties(std::vector<P::Ids> propertyIds, std::vector<tinyxml2::XMLElement*> propertyValues);
		static void addEntityToFields(Entity entity, tinyxml2::XMLElement* fieldsElem);
		static void addBehaviorsToEntity();

		template<typename T>
		static T interpretPropertyValue(tinyxml2::XMLElement* value); // Interprets an XML element that holds the value of a property and converts it into the specified type 

		template<> static int interpretPropertyValue<int>(tinyxml2::XMLElement* value);
		template<> static double interpretPropertyValue<double>(tinyxml2::XMLElement* value);
		template<> static bool interpretPropertyValue<bool>(tinyxml2::XMLElement* value);
};