#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <exception>

#include "World.h"
#include "Field.h"
#include "Fields.h"
#include "Entity.h"
#include "Properties.h"

#include "tinyxml2.h"

class World;

class EntityFactory
{
	public:
		static World createWorld(std::string path);

		static Entity createEntityFromProperties(tinyxml2::XMLElement* propertiesElem);
		static Entity createEntityFromProperties(std::vector<P::Ids> propertyIds, std::vector<tinyxml2::XMLElement*> propertyValues);
		static std::vector<Fields::Ids> convertFieldElemsToFieldIds(tinyxml2::XMLElement* fieldsElem);

		template<typename T>
		static T interpretPropertyValue(tinyxml2::XMLElement* value); // Interprets an XML element that holds the value of a property and converts it into the specified type

		template<> static int interpretPropertyValue<int>(tinyxml2::XMLElement* value);
		template<> static double interpretPropertyValue<double>(tinyxml2::XMLElement* value);
		template<> static bool interpretPropertyValue<bool>(tinyxml2::XMLElement* value);
		template<> static sf::Color interpretPropertyValue<sf::Color>(tinyxml2::XMLElement* value);
		template<> static Point interpretPropertyValue<Point>(tinyxml2::XMLElement* value);
};