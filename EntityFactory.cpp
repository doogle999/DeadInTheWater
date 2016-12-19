#include "EntityFactory.h"

#define ADD_PROPERTY_CASE(NAME) case P::Ids:: ## NAME: entity.AXS(NAME) = interpretPropertyValue<P::TYPE_ ## NAME>(propertyValues[i]); break;

//World EntityFactory::createWorld(std::string path)
//{
//	/* 
//	<ENTITIES>
//		<ENTITY>
//			<PROPERTIES>
//				<PROPERTY>
//					<NAME> </NAME>
//					<VALUE> </VALUE>
//				</PROPERTY>
//			</PROPERTIES>
//			<FIELDS>
//				<FIELD>
//					<NAME> </NAME>
//				</FIELD>
//			</FIELDS>
//			<BEHAVIORS>
//				<BEHAVIOR>
//					<NAME> </NAME>
//					<GROUP> </GROUP>
//				</BEHAVIOR>
//			</BEHAVIORS>
//		</ENTITY>
//	<ENTITIES>
//	*/
//
//	tinyxml2::XMLDocument document;
//	document.LoadFile(path.c_str());
//
//	if(document.ErrorID() != 0)
//	{
//		assert(0 && document.ErrorName());
//	}
//
//	World world;
//
//	std::vector<size_t> temporaryEntitiesVector;
//
//	for(unsigned int i = 0; i < World::fields.size(); i++)
//	{
//		world.fieldEntities[World::fields[i]] = temporaryEntitiesVector;
//	}	
//
//	world.currentEntities = 0;
//	for(tinyxml2::XMLElement* entityXMLElement = document.FirstChildElement("ENTITIES")->FirstChildElement("ENTITY"); entityXMLElement != NULL; entityXMLElement = entityXMLElement->NextSiblingElement("ENTITY"))
//	{
//		world.entities[world.currentEntities] = createEntity(entityXMLElement, &world);
//
//		world.currentEntities += 1;
//		if(world.currentEntities == World::MAX_ENTITIES)
//		{
//			break;
//		}
//	}
//
//	return world;
//}
//
//Entity EntityFactory::createEntity(tinyxml2::XMLElement* entityElem, World* parentWorld)
//{	
//	Entity entity = createEntityFromProperties(entityElem->FirstChildElement("PROPERTIES"));
//
//	// Dealing with fields
//	tinyxml2::XMLElement* fieldsXMLElement = entityElem->FirstChildElement("FIELDS");
//	for(tinyxml2::XMLElement* fieldXMLElement = fieldsXMLElement->FirstChildElement("FIELD"); fieldXMLElement; fieldXMLElement = fieldXMLElement->NextSiblingElement("FIELD"))
//	{
//		Field* fieldPointer = World::fields.at(std::find(World::fieldNames.begin(), World::fieldNames.end(), fieldXMLElement->FirstChildElement("NAME")->GetText()) - World::fieldNames.begin());
//		if(entity.compatible(fieldPointer))
//		{
//			parentWorld->fieldEntities.at(fieldPointer).push_back(parentWorld->currentEntities);
//		}
//		else
//		{
//			assert(0 && "Attempted to create an entity with a behavior that it doesn't have the necessary properties for");
//		}
//	}
//
//	// Dealing with behaviors
//	tinyxml2::XMLElement* behaviorsXMLElement = entityXMLElement->FirstChildElement("BEHAVIORS");
//	for(tinyxml2::XMLElement* behaviorXMLElement = behaviorsXMLElement->FirstChildElement("BEHAVIOR"); behaviorXMLElement; behaviorXMLElement = behaviorXMLElement->NextSiblingElement("BEHAVIOR"))
//	{
//		std::string behaviorName = behaviorXMLElement->FirstChildElement("NAME")->GetText();
//		size_t pos = behaviorName.find("::");
//		if(pos != std::string::npos) // Checks if the behavior is part of a field
//		{
//			Field* behaviorParentField = World::fields.at(std::find(World::fieldNames.begin(), World::fieldNames.end(), behaviorName.substr(0, pos)) - World::fieldNames.begin());
//			if(parentWorld->fieldEntities.at(behaviorParentField).empty())
//			{
//				assert(0 && "Attempted to create an entity with a behavior whose parent field it is not in");
//			}
//			if(parentWorld->fieldEntities.at(behaviorParentField).back() != parentWorld->currentEntities)
//			{
//				assert(0 && "Attempted to create an entity with a behavior whose parent field it is not in");
//			}
//		}
//
//		Behavior* behaviorPointer = World::behaviors.at(std::find(World::behaviorNames.begin(), World::behaviorNames.end(), behaviorName) - World::behaviorNames.begin());
//		if(entity.compatible(behaviorPointer))
//		{
//			std::string group = behaviorXMLElement->FirstChildElement("GROUP")->GetText();
//			if(group == "INPUTERS")
//			{
//				entity.inputers.push_back(behaviorPointer);
//			}
//			else if(group == "UPDATERS")
//			{
//				entity.updaters.push_back(behaviorPointer);
//			}
//			else if(group == "RENDERERS")
//			{
//				entity.renderers.push_back(behaviorPointer);
//			}
//			else
//			{
//				assert(0 && "Attempted to create an entity with a behavior in a group that doesn't exist");
//			}
//		}
//		else
//		{
//			assert(0 && "Attempted to create an entity with a behavior that it doesn't have the necessary properties for");
//		}
//	}
//
//	return entity;
//}
//
//Entity EntityFactory::createEntityFromProperties(tinyxml2::XMLElement* propertiesElem)
//{
//	std::vector<P::Ids> propertyIds;
//	std::vector<tinyxml2::XMLElement*> propertyValues;
//
//	for(tinyxml2::XMLElement* propertyElem = propertiesElem ->FirstChildElement("PROPERTY"); propertyElem; propertyElem = propertyElem->NextSiblingElement("PROPERTY"))
//	{
//		try
//		{
//			propertyIds.push_back(P::Names.at(propertyElem->FirstChildElement("NAME")->GetText()));
//			propertyValues.push_back(propertyElem->FirstChildElement("VALUE"));
//		}
//		catch(std::out_of_range e) // The property was not recognized or its name is not in the P::Names map
//		{
//			printf(e.what());
//		}
//	}
//
//	return createEntityFromProperties(propertyIds, propertyValues);
//}
//Entity EntityFactory::createEntityFromProperties(std::vector<P::Ids> propertyIds, std::vector<tinyxml2::XMLElement*> propertyValues)
//{
//	Entity entity(propertyIds);
//
//	for(unsigned int i = 0; i < propertyIds.size(); i++)
//	{
//		switch(propertyIds[i]) // All properties need to have a case here if they are to be used
//		{
//			ADD_PROPERTY_CASE(xPosition)
//			ADD_PROPERTY_CASE(yPosition)
//			ADD_PROPERTY_CASE(xVelocity)
//			ADD_PROPERTY_CASE(yVelocity)
//			ADD_PROPERTY_CASE(selected)
//			ADD_PROPERTY_CASE(radius)
//
//			default: assert(0 && "EntityFactory is missing a property case"); // Not an exception because only valid property ids can get to this switch
//		}
//	}
//
//	return entity;
//}
//void EntityFactory::addEntityToFields(Entity entity, tinyxml2::XMLElement* fieldsElem)
//{
//	for(tinyxml2::XMLElement* fieldElem = fieldsElem->FirstChildElement("FIELD"); fieldElem; fieldElem = fieldElem->NextSiblingElement("FIELD"))
//	{
//		Field* fieldPointer = World::fields.at(std::find(World::fieldNames.begin(), World::fieldNames.end(), fieldElem->FirstChildElement("NAME")->GetText()) - World::fieldNames.begin());
//		if(entity.compatible(fieldPointer))
//		{
//			parentWorld->fieldEntities.at(fieldPointer).push_back(parentWorld->currentEntities);
//		}
//		else
//		{
//			assert(0 && "Attempted to create an entity with a behavior that it doesn't have the necessary properties for");
//		}
//	}
//}
//
//template<> int EntityFactory::interpretPropertyValue<int>(tinyxml2::XMLElement* value)
//{
//	return std::stoi(value->GetText());
//}
//template<> double EntityFactory::interpretPropertyValue<double>(tinyxml2::XMLElement* value)
//{
//	return std::stod(value->GetText());
//}
//template<> bool EntityFactory::interpretPropertyValue<bool>(tinyxml2::XMLElement* value)
//{
//	return (strcmp(value->GetText(), "0") != 0);
//}

#undef ADD_PROPERTY_CASE