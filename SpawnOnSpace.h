#pragma once

#include "SFML/Window/Keyboard.hpp"

#include "Behavior.h"
#include "Entity.h"

class SpawnOnSpace : public Behavior
{
	public:
		SpawnOnSpace();

		~SpawnOnSpace();

		virtual void run(Entity& e);

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;
};