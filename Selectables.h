#pragma once

#include <vector>

#include "Properties.h"
#include "Entity.h"
#include "Field.h"

class Field;
class Entity;

class Selectables : public Field
{
	public:
		Selectables();

		~Selectables();

		virtual void input();

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;

		bool firstSelected;
};