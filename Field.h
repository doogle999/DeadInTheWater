#pragma once

#include "Entity.h"
#include "Properties.h"
#include "EntityFactory.h"

class EntityFactory;
class Entity;

class Field
{
	public:
		virtual void initialize() = 0;

		virtual std::vector<P::Ids> getNecessaryProperties() = 0;

	protected:
		std::vector<Entity*> entities;

	friend EntityFactory;
};