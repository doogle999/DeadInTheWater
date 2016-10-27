#pragma once

#include <SFML/Window/Mouse.hpp>

#include "InputComponent.h"

class TowardsMouseIC : public InputComponent
{
	public:
		TowardsMouseIC();

		virtual void input(Entity& e, sf::Window* w);

		~TowardsMouseIC();
};

