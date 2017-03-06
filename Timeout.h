#pragma once

#include "SFML\Window\Keyboard.hpp"

#include <vector>

#include "Entity.h"
#include "Field.h"
#include "EntityFactory.h"

class Entity;
class Camera2D;

class Timeout : public Field
{
	public:
		Timeout();

		~Timeout();

		virtual void update();

		virtual std::vector<Attribute::Ids> getNecessaryProperties();

	private:
		static const std::vector<Attribute::Ids> necessaryProperties;
};