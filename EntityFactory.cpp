#include "EntityFactory.h"

#define ADD_PROPERTY_CASE(NAME) case P::Ids:: ## NAME: entity.AXS(NAME) = interpretPropertyValue<P::TYPE_ ## NAME>(propertyValues[i]); break;

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
		world.scheduleToSpawn(createEntityFromProperties(entityElem->FirstChildElement("PROPERTIES")), convertFieldElemsToFieldIds(entityElem->FirstChildElement("FIELDS")));
	}

	return world;
}

Entity EntityFactory::createEntityFromProperties(tinyxml2::XMLElement* propertiesElem)
{
	std::vector<P::Ids> propertyIds;
	std::vector<tinyxml2::XMLElement*> propertyValues;

	for(tinyxml2::XMLElement* propertyElem = propertiesElem ->FirstChildElement("PROPERTY"); propertyElem; propertyElem = propertyElem->NextSiblingElement("PROPERTY"))
	{
		try
		{
			propertyIds.push_back(P::Names.at(propertyElem->FirstChildElement("NAME")->GetText()));
			propertyValues.push_back(propertyElem->FirstChildElement("VALUE"));
		}
		catch(std::out_of_range e) // The property was not recognized or its name is not in the P::Names map
		{
			printf("Error recognizing property %s \n", propertyElem->FirstChildElement("NAME")->GetText());
		}
	}

	return createEntityFromProperties(propertyIds, propertyValues);
}
Entity EntityFactory::createEntityFromProperties(std::vector<P::Ids> propertyIds, std::vector<tinyxml2::XMLElement*> propertyValues)
{
	Entity entity(propertyIds);

	for(unsigned int i = 0; i < propertyIds.size(); i++)
	{
		switch(propertyIds[i]) // All properties need to have a case here if they are to be used
		{
			ADD_PROPERTY_CASE(xPosition)
			ADD_PROPERTY_CASE(yPosition)
			ADD_PROPERTY_CASE(xVelocity)
			ADD_PROPERTY_CASE(yVelocity)
			ADD_PROPERTY_CASE(xAcceleration)
			ADD_PROPERTY_CASE(yAcceleration)
			ADD_PROPERTY_CASE(selected)
			ADD_PROPERTY_CASE(radius)
			ADD_PROPERTY_CASE(mass)
			ADD_PROPERTY_CASE(reloadTime)
			ADD_PROPERTY_CASE(color)
			ADD_PROPERTY_CASE(renderRadius)
			ADD_PROPERTY_CASE(timeoutTime)

			default: assert(0 && "EntityFactory is missing a property case"); // Not an exception because only valid property ids can get to this switch
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
		catch(std::out_of_range e) // The field was not recognized or its name is not in Fields::FieldRegistry for some reason (cough cough Ajax you idiot you forgot to register it again cough cough)
		{
			printf("Error recognizing field %s \n", fieldElem->FirstChildElement("NAME")->GetText());
		}
	}

	return f;
}

template<> int EntityFactory::interpretPropertyValue<int>(tinyxml2::XMLElement* value)
{
	return std::stoi(value->GetText());
}
template<> double EntityFactory::interpretPropertyValue<double>(tinyxml2::XMLElement* value)
{
	return std::stod(value->GetText());
}
template<> bool EntityFactory::interpretPropertyValue<bool>(tinyxml2::XMLElement* value)
{
	return (strcmp(value->GetText(), "0") != 0);
}
template<> sf::Color EntityFactory::interpretPropertyValue<sf::Color>(tinyxml2::XMLElement* value)
{
	return sf::Color
	(
		interpretPropertyValue<int>(value->FirstChildElement("RED")),
		interpretPropertyValue<int>(value->FirstChildElement("GREEN")),
		interpretPropertyValue<int>(value->FirstChildElement("BLUE")),
		interpretPropertyValue<int>(value->FirstChildElement("ALPHA"))
	);
}

#undef ADD_PROPERTY_CASE