#pragma once

#include <SFML/Window/Keyboard.hpp>

#include "InputComponent.h"

class ArrowVelocityIC : public InputComponent
{
	public:
		ArrowVelocityIC();
		
		virtual void input(Entity& e, sf::Window* w);

		~ArrowVelocityIC();
};

