#pragma once

#include <vector>

#include "Entity.h"
#include "Properties.h"

class Entity;

class Field
{
	public:
		void initialize(std::vector<Entity*> e);

		virtual std::vector<P::Ids> getNecessaryProperties() = 0;

	protected:
		std::vector<Entity*> entities;
};