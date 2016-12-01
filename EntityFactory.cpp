#include "EntityFactory.h"

#define ADD_PROPERTY_CASE(NAME) case P::Ids:: ## NAME: entity.AXS(NAME) = interpretPropertyValue<P::TYPE_ ## NAME>(propertyValues[i]); break;


World EntityFactory::createWorld(std::string path)
{
	/* 
	<ENTITIES>
		<ENTITY>
			<PROPERTIES>
				<PROPERTY>
					<NAME> </NAME>
					<VALUE> </VALUE>
				</PROPERTY>
			</PROPERTIES>
			<FIELDS>
				<FIELD>
					<NAME> </NAME>
				</FIELD>
			</FIELDS>
			<BEHAVIORS>
				<BEHAVIOR>
					<NAME> </NAME>
					<GROUP> </GROUP>
				</BEHAVIOR>
			</BEHAVIORS>
		</ENTITY>
	<ENTITIES>
	*/

	tinyxml2::XMLDocument document;
	document.LoadFile(path.c_str());

	if(document.ErrorID() != 0)
	{
		assert(0 && document.ErrorName());
	}

	World world;

	std::vector<size_t> temporaryEntitiesVector;

	for(unsigned int i = 0; i < World::fields.size(); i++)
	{
		world.fieldEntities[World::fields[i]] = temporaryEntitiesVector;
	}	

	size_t entityCounter = 0;
	for(tinyxml2::XMLElement* entityXMLElement = document.FirstChildElement("ENTITY"); entityXMLElement != NULL; entityXMLElement = entityXMLElement->NextSiblingElement("ENTITY"))
	{
		world.entities[entityCounter] = createEntity(entityXMLElement, &world, entityCounter);

		entityCounter += 1;
		if(entityCounter == World::MAX_ENTITIES)
		{
			break;
		}
	}

	return world;
}

Entity EntityFactory::createEntity(tinyxml2::XMLElement* entityXMLElement, World* parentWorld, size_t location)
{
	// Dealing with properties
	std::vector<P::Ids> propertyIds;
	std::vector<tinyxml2::XMLElement*> propertyValues; // The reason we use an element is that, if we were to store more complex types than primitives, we might need a sub strcture

	tinyxml2::XMLElement* propertiesXMLElement = entityXMLElement->FirstChildElement("PROPERTIES");
	for(tinyxml2::XMLElement* propertyXMLElement = propertiesXMLElement->FirstChildElement("PROPERTY"); propertyXMLElement; propertyXMLElement = propertyXMLElement->NextSiblingElement("PROPERTY"))
	{
		propertyIds.push_back(P::Names.at(propertyXMLElement->FirstChildElement("NAME")->GetText()));
		propertyValues.push_back(propertyXMLElement->FirstChildElement("VALUE"));
	}

	Entity entity(propertyIds);

	for(unsigned int i = 0; i < propertyIds.size(); i++) // Iterate through the properties list
	{
		switch(propertyIds[i]) // Check which property it is and then set that property, fails if the property was not recognized
		{
			ADD_PROPERTY_CASE(xPosition)
			ADD_PROPERTY_CASE(yPosition)
			ADD_PROPERTY_CASE(xVelocity)
			ADD_PROPERTY_CASE(yVelocity)
			ADD_PROPERTY_CASE(radius)

			default: assert(0 && "Attempted to create an entity with a property that does not exist");
		}
	}

	// Dealing with fields
	tinyxml2::XMLElement* fieldsXMLElement = entityXMLElement->FirstChildElement("FIELDS");
	for(tinyxml2::XMLElement* fieldXMLElement = fieldsXMLElement->FirstChildElement("FIELD"); fieldXMLElement; fieldXMLElement = fieldXMLElement->NextSiblingElement("FIELD"))
	{
		Field* fieldPointer = World::fields.at(std::find(World::fieldNames.begin(), World::fieldNames.end(), fieldXMLElement->FirstChildElement("NAME")->GetText()) - World::fieldNames.begin());
		if(entity.compatible(fieldPointer))
		{
			parentWorld->fieldEntities.at(fieldPointer).push_back(location);
		}
		else
		{
			assert(0 && "Attempted to create an entity with a behavior that it doesn't have the necessary properties for");
		}
	}

	// Dealing with behaviors
	tinyxml2::XMLElement* behaviorsXMLElement = entityXMLElement->FirstChildElement("BEHAVIORS");
	for(tinyxml2::XMLElement* behaviorXMLElement = behaviorsXMLElement->FirstChildElement("BEHAVIOR"); behaviorXMLElement; behaviorXMLElement = behaviorXMLElement->NextSiblingElement("BEHAVIOR"))
	{
		std::string behaviorName = behaviorXMLElement->FirstChildElement("NAME")->GetText();
		size_t pos = behaviorName.find("::");
		if(pos != std::string::npos) // Checks if the behavior is part of a field
		{
			Field* behaviorParentField = World::fields.at(std::find(World::fieldNames.begin(), World::fieldNames.end(), behaviorName.substr(0, pos)) - World::fieldNames.begin());
			if(parentWorld->fieldEntities.at(behaviorParentField).empty())
			{
				assert(0 && "Attempted to create an entity with a behavior whose parent field it is not in");
			}
			if(parentWorld->fieldEntities.at(behaviorParentField).back() != location)
			{
				assert(0 && "Attempted to create an entity with a behavior whose parent field it is not in");
			}
		}

		Behavior* behaviorPointer = World::behaviors.at(std::find(World::behaviorNames.begin(), World::behaviorNames.end(), behaviorName) - World::behaviorNames.begin());
		if(entity.compatible(behaviorPointer))
		{
			std::string group = behaviorXMLElement->FirstChildElement("GROUP")->GetText();
			if(group == "INPUTERS")
			{
				entity.inputers.push_back(behaviorPointer);
			}
			else if(group == "UPDATERS")
			{
				entity.updaters.push_back(behaviorPointer);
			}
			else if(group == "RENDERERS")
			{
				entity.renderers.push_back(behaviorPointer);
			}
			else
			{
				assert(0 && "Attempted to create an entity with a behavior in a group that doesn't exist");
			}
		}
		else
		{
			assert(0 && "Attempted to create an entity with a behavior that it doesn't have the necessary properties for");
		}
	}

	return entity;
}

template<> int EntityFactory::interpretPropertyValue<int>(tinyxml2::XMLElement* value)
{
	return std::stoi(value->GetText());
}
template<> double EntityFactory::interpretPropertyValue<double>(tinyxml2::XMLElement* value)
{
	return std::stod(value->GetText());
}

#undef ADD_PROPERTY_CASE