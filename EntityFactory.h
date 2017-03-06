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
#include "Attribute.h"
#include "Attributes.h"

#include "tinyxml2.h"

class World;

class EntityFactory
{
	public:
		static World createWorld(std::string path);

		static Entity createEntityFromAttributes(tinyxml2::XMLElement* attributeElem);
		static Entity createEntityFromAttributes(std::vector<Attribute::Ids> attributeIds, std::vector<tinyxml2::XMLElement*> attributeValues);
		static std::vector<Fields::Ids> convertFieldElemsToFieldIds(tinyxml2::XMLElement* fieldsElem);

		template<typename T>
		static T interpretAttributeValue(tinyxml2::XMLElement* value); // Interprets an XML element that holds the value of a property and converts it into the specified type

		template<> static int interpretAttributeValue<int>(tinyxml2::XMLElement* value);
		template<> static double interpretAttributeValue<double>(tinyxml2::XMLElement* value);
		template<> static bool interpretAttributeValue<bool>(tinyxml2::XMLElement* value);
		template<> static PVector<double, 2> interpretAttributeValue<PVector<double, 2>>(tinyxml2::XMLElement* value);
		template<> static Polygon<double> interpretAttributeValue<Polygon<double>>(tinyxml2::XMLElement* value);
		template<> static A::Translation interpretAttributeValue<A::Translation>(tinyxml2::XMLElement* value);
		template<> static A::TimeoutTime interpretAttributeValue<A::TimeoutTime>(tinyxml2::XMLElement* value);
		template<> static A::ReloadTime interpretAttributeValue<A::ReloadTime>(tinyxml2::XMLElement* value);
};