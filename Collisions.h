#pragma once

#include <vector>

#include "Properties.h"
#include "Entity.h"
#include "Field.h"

class Field;
class Entity;

class Collisions : public Field
{
	public:
		Collisions();
			
		~Collisions();

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;

		bool collision(Entity& e);
};