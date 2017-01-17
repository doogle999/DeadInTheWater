#pragma once

#include "SFML\Window\Keyboard.hpp"

#include <vector>

#include "Properties.h"
#include "Entity.h"
#include "Field.h"
#include "EntityFactory.h"

class Entity;
class Camera2D;

class SpawnProjectile : public Field
{
	public:
		SpawnProjectile();

		~SpawnProjectile();

		virtual void input();

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;

		static const double cooldown;
};