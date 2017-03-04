#include "EntityFactory.h"

#define ADD_PROPERTY_CASE(NAME) case P::Ids:: ## NAME: { P::TYPE_ ## NAME temp; temp = interpretPropertyValue<P::TYPE_ ## NAME>(propertyValues[i]); std::memcpy(&entity.AXS(NAME), &temp, sizeof(temp)); break; }

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
			ADD_PROPERTY_CASE(position)
			ADD_PROPERTY_CASE(velocity)
			ADD_PROPERTY_CASE(acceleration)
			ADD_PROPERTY_CASE(orientation)
			ADD_PROPERTY_CASE(orientationVelocity)
			ADD_PROPERTY_CASE(reloadTime)
			ADD_PROPERTY_CASE(timeoutTime)
			case P::Ids::hitPolygon: 
			{ 
				P::TYPE_hitPolygon polygkrejgjers;

				unsigned char* bytes = reinterpret_cast<unsigned char*>(&entity.properties);
				size_t j;

				printf("[ ");
				for(j = 0; j < sizeof(double) + 3 * sizeof(PVector<double, 2>) + sizeof(Polygon<double>); j++)
				{
					printf("%02x ", bytes[i]);
				}
				printf("]\n");


				bytes = reinterpret_cast<unsigned char*>(&polygkrejgjers);

				printf("[ ");
				for(j = 0; j < sizeof(Polygon<double>); j++)
				{
					printf("%02x ", bytes[i]);
				}
				printf("]\n");

				bool b = std::is_trivially_copyable<PVector<double, 2>>::value;


				entity.AXS(hitPolygon) = (interpretPropertyValue<P::TYPE_hitPolygon>(propertyValues[i]));
				std::memcpy(&entity.AXS(hitPolygon), &polygkrejgjers, sizeof(Polygon<double>));
				break;
			}
			//ADD_PROPERTY_CASE(hitPolygon)

			default: assert(0 && "EntityFactory is missing a property case"); // Not an exception because only valid property ids can get to this switch
		}
	}

	Polygon<double> bozo3 = reinterpret_cast<Polygon<double>&>(entity.access<void*>(P::Ids::hitPolygon));
	double aaaaaaa = bozo3.points[1].c[0];

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
template<> PVector<double, 2> EntityFactory::interpretPropertyValue<PVector<double, 2>>(tinyxml2::XMLElement* value)
{
	return PVector<double, 2>
	(
		{ interpretPropertyValue<double>(value->FirstChildElement("X")),
		interpretPropertyValue<double>(value->FirstChildElement("Y")) }
	);
}
template<> Polygon<double> EntityFactory::interpretPropertyValue<Polygon<double>>(tinyxml2::XMLElement* value)
{
	Polygon<double> poly;

	for(tinyxml2::XMLElement* pointElem = value->FirstChildElement("POINT"); pointElem; pointElem = pointElem->NextSiblingElement("POINT"))
	{
		poly.points.push_back(interpretPropertyValue<PVector<double, 2>>(pointElem));
	}

	return poly;
}
#undef ADD_PROPERTY_CASE