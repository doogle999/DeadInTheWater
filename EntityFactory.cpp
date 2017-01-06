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

	for(unsigned int i = 0; i < world.fieldEntities.size(); i++)
	{
		world.fieldEntities[World.fields[i]] = temporaryEntitiesVector;
	}	

	world.currentEntityCount = 0;
	for(tinyxml2::XMLElement* entityElem = document.FirstChildElement("ENTITIES")->FirstChildElement("ENTITY"); entityElem != NULL; entityElem = entityElem->NextSiblingElement("ENTITY"))
	{
		world.entities[world.currentEntityCount] = createEntity(entityElem, &world);
		
		world.currentEntityCount += 1;
		if(world.currentEntityCount == World::MAX_ENTITIES)
		{
			break;
		}
	}

	for(unsigned int i = 0; i < world.fields.size(); i++)
	{
		std::vector<Entity*> e;
		e.reserve(world.fieldEntities.at(world.fields[i]).size());
		for(unsigned int j = 0; j < world.fieldEntities.at(world.fields[i]).size(); j++)
		{
			e.push_back(&world.entities[world.fieldEntities.at(world.fields[i])[j]]);
		}
		world.fields[i]->initialize(e);
	}

	return world;
}

Entity EntityFactory::createEntity(tinyxml2::XMLElement* entityElem, World* world)
{
	Entity entity = createEntityFromProperties(entityElem->FirstChildElement("PROPERTIES"));
	addEntityToFields(entity, entityElem->FirstChildElement("FIELDS"), world);
	addBehaviorsToEntity(entity, entityElem->FirstChildElement("BEHAVIORS"), world);

	return entity;
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
			printf(e.what());
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

			default: assert(0 && "EntityFactory is missing a property case"); // Not an exception because only valid property ids can get to this switch
		}
	}

	return entity;
}
void EntityFactory::addEntityToFields(Entity& entity, tinyxml2::XMLElement* fieldsElem, World* world)
{
	for(tinyxml2::XMLElement* fieldElem = fieldsElem->FirstChildElement("FIELD"); fieldElem; fieldElem = fieldElem->NextSiblingElement("FIELD"))
	{
		Field* fieldPointer = world->fields.at(Fields::fieldRegistry.at(fieldElem->FirstChildElement("NAME")->GetText()));
		if(entity.compatible(fieldPointer))
		{
			world->fieldEntities.at(fieldPointer).push_back(world->currentEntityCount);
		}
		else
		{
			printf("Attempted to put an Entity in a filed it is not compatible with");
		}
	}
}
void EntityFactory::addBehaviorsToEntity(Entity& entity, tinyxml2::XMLElement* behaviorsElem, World* world)
{
	bool inParentField = true;

	for(tinyxml2::XMLElement* behaviorElem = behaviorsElem->FirstChildElement("BEHAVIOR"); behaviorElem; behaviorElem = behaviorElem->NextSiblingElement("BEHAVIOR"))
	{
		std::string behaviorName = behaviorElem->FirstChildElement("NAME")->GetText();
		size_t pos = behaviorName.find("::");
		if(pos != std::string::npos) // Checks if the behavior is part of a field
		{
			Field* behaviorParentField = world->fields.at(Fields::fieldRegistry.at(behaviorName.substr(0, pos)));
			if(world->fieldEntities.at(behaviorParentField).empty())
			{
				printf("Attempted to create an entity with a behavior whose parent field it is not in");
				inParentField = false;
			}
			if(world->fieldEntities.at(behaviorParentField).back() != world->currentEntityCount)
			{
				printf("Attempted to create an entity with a behavior whose parent field it is not in");
				inParentField = false;
			}
		}

		Behavior* behaviorPointer = world->behaviors.at(Behaviors::behaviorRegistry.at(behaviorName));
		if(entity.compatible(behaviorPointer) && inParentField)
		{
			std::string group = behaviorElem->FirstChildElement("GROUP")->GetText();
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
				printf("Attempted to create an entity with a behavior in a group that doesn't exist");
			}
		}
		else
		{
			printf("Attempted to create an entity with a behavior that it doesn't have the necessary properties for");
		}
	}
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