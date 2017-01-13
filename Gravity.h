#pragma once

#include <vector>

#include "Properties.h"
#include "Entity.h"
#include "Field.h"

class Entity;

class Gravity : public Field
{
	public:
		Gravity();
			
		~Gravity();

		virtual void update();

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;

		static const double GRAV_CONSTANT;
};