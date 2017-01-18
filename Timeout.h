#pragma once

#include "SFML\Window\Keyboard.hpp"

#include <vector>

#include "Properties.h"
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

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;
};