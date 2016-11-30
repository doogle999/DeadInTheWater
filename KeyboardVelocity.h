#pragma once

#include "SFML/Window/Keyboard.hpp"

#include "Behavior.h"
#include "Entity.h"

class KeyboardVelocity : public Behavior
{
	public:
		KeyboardVelocity();

		~KeyboardVelocity();

		virtual void run(Entity& e);

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;
};