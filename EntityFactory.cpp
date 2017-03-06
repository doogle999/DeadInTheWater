#include "EntityFactory.h"

#define ADD_ATTRIBUTE_ASSIGNMENT_CASE(NAME) case Attribute::Ids:: ## NAME: { entity.AXS(NAME) = interpretAttributeValue<A:: ## NAME>(attributeValues[i]); break; }

World EntityFactory::createWorld(std::string path)
{
	tinyxml2::XMLDocument document;
	document.LoadFile(path.c_str());

	if(document.ErrorID() != 0)
	{
		assert(0 && document.ErrorName());
	}

	World world;

	for(tinyxml2::XMLElement* entityElem = document.FirstChildElement("ENTITIES")->FirstChildElement("ENTITY"); entityElem != NULL; entityElem = entityElem->NextSiblingElement("ENTITY"))
	{
		world.scheduleToSpawn(createEntityFromAttributes(entityElem->FirstChildElement("ATTRIBUTES")), convertFieldElemsToFieldIds(entityElem->FirstChildElement("FIELDS")));
	}

	return world;
}

Entity EntityFactory::createEntityFromAttributes(tinyxml2::XMLElement* attributesElem)
{
	std::vector<Attribute::Ids> attributeIds;
	std::vector<tinyxml2::XMLElement*> attributeValues;

	for(tinyxml2::XMLElement* attributeElem = attributesElem->FirstChildElement("ATTRIBUTE"); attributeElem; attributeElem = attributeElem->NextSiblingElement("ATTRIBUTE"))
	{
		auto nameId = std::find(Attribute::ATTRIBUTE_NAMES.begin(), Attribute::ATTRIBUTE_NAMES.end(), attributeElem->FirstChildElement("NAME")->GetText());

		if(nameId != Attribute::ATTRIBUTE_NAMES.end())
		{
			attributeIds.push_back(static_cast<Attribute::Ids>(nameId - Attribute::ATTRIBUTE_NAMES.begin()));
			tinyxml2::XMLElement* meme = attributeElem->FirstChildElement("VALUE");
			attributeValues.push_back(attributeElem->FirstChildElement("VALUE"));
		}
		else
		{
			printf("Error recognizing attribute %s \n", attributeElem->FirstChildElement("NAME")->GetText());
		}
	}

	return createEntityFromAttributes(attributeIds, attributeValues);
}
Entity EntityFactory::createEntityFromAttributes(std::vector<Attribute::Ids> attributeIds, std::vector<tinyxml2::XMLElement*> attributeValues)
{
	Entity entity(attributeIds);

	for(unsigned int i = 0; i < attributeIds.size(); i++)
	{
		switch(attributeIds[i])
		{
			ADD_ATTRIBUTE_ASSIGNMENT_CASE(Translation)
			ADD_ATTRIBUTE_ASSIGNMENT_CASE(TimeoutTime)
			ADD_ATTRIBUTE_ASSIGNMENT_CASE(ReloadTime)
			
			default: assert(0 && "EntityFactory is missing an attribute case"); // Not an exception because only valid attribute ids can get to this switch
		}
	}

	return entity;
}
std::vector<Fields::Ids> EntityFactory::convertFieldElemsToFieldIds(tinyxml2::XMLElement* fieldsElem)
{
	std::vector<Fields::Ids> f;
	for(tinyxml2::XMLElement* fieldElem = fieldsElem->FirstChildElement("FIELD"); fieldElem; fieldElem = fieldElem->NextSiblingElement("FIELD"))
	{
		try
		{
			f.push_back(Fields::fieldRegistry.at(fieldElem->FirstChildElement("NAME")->GetText()));
		}
		catch(std::out_of_range e) // The field was not recognized or its name is not in Fields::FieldRegistry for some reason
		{
			printf("Error recognizing field %s \n", fieldElem->FirstChildElement("NAME")->GetText());
		}
	}

	return f;
}

template<> int EntityFactory::interpretAttributeValue<int>(tinyxml2::XMLElement* value)
{
	return std::stoi(value->GetText());
}
template<> double EntityFactory::interpretAttributeValue<double>(tinyxml2::XMLElement* value)
{
	return std::stod(value->GetText());
}
template<> bool EntityFactory::interpretAttributeValue<bool>(tinyxml2::XMLElement* value)
{
	return (strcmp(value->GetText(), "0") != 0);
}
template<> PVector<double, 2> EntityFactory::interpretAttributeValue<PVector<double, 2>>(tinyxml2::XMLElement* value)
{
	return PVector<double, 2>
	(
		{ interpretAttributeValue<double>(value->FirstChildElement("X")),
		interpretAttributeValue<double>(value->FirstChildElement("Y")) }
	);
}
template<> Polygon<double> EntityFactory::interpretAttributeValue<Polygon<double>>(tinyxml2::XMLElement* value)
{
	Polygon<double> poly;

	for(tinyxml2::XMLElement* pointElem = value->FirstChildElement("POINT"); pointElem; pointElem = pointElem->NextSiblingElement("POINT"))
	{
		poly.points.push_back(interpretAttributeValue<PVector<double, 2>>(pointElem));
	}

	return poly;
}
template<> A::Translation EntityFactory::interpretAttributeValue<A::Translation>(tinyxml2::XMLElement* value)
{
	A::Translation returnValue;

	returnValue.position = interpretAttributeValue<PVector<double, 2>>(value->FirstChildElement("POSITION"));
	returnValue.velocity = interpretAttributeValue<PVector<double, 2>>(value->FirstChildElement("VELOCITY"));
	returnValue.acceleration = interpretAttributeValue<PVector<double, 2>>(value->FirstChildElement("ACCELERATION"));

	return returnValue;
}
template<> A::TimeoutTime EntityFactory::interpretAttributeValue<A::TimeoutTime>(tinyxml2::XMLElement* value)
{
	A::TimeoutTime returnValue;

	returnValue.currentTimeoutTime = interpretAttributeValue<double>(value->FirstChildElement("CURRENT_TIMEOUT_TIME"));

	return returnValue;
}
template<> A::ReloadTime EntityFactory::interpretAttributeValue<A::ReloadTime>(tinyxml2::XMLElement* value)
{
	A::ReloadTime returnValue;

	returnValue.reloadTime = interpretAttributeValue<double>(value->FirstChildElement("RELOAD_TIME"));
	returnValue.currentReloadTime = interpretAttributeValue<double>(value->FirstChildElement("CURRENT_RELOAD_TIME"));

	return returnValue;
}
#undef ADD_ATTRIBUTE_ASSIGNMENT_CASE