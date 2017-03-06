#pragma once

#include "SFML\Window\Keyboard.hpp"

#include <vector>

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

		virtual void update();

		virtual std::vector<Attribute::Ids> getNecessaryProperties();

	private:
		static const std::vector<Attribute::Ids> necessaryProperties;

		static const double cooldown;
};