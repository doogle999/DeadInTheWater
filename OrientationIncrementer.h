#pragma once

#include "Entity.h"
#include "Field.h"
#include "Fields.h"

class Entity;

class OrientationIncrementer : public Field
{
	public:
		OrientationIncrementer();

		~OrientationIncrementer();

		virtual void update();

		virtual std::vector<Attribute::Ids> getNecessaryProperties();

	private:
		static const std::vector<Attribute::Ids> necessaryProperties;
};

