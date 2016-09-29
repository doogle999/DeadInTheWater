#pragma once

#include <vector>
#include <iostream>

#include <SFML/Window/Keyboard.hpp>

class InputHandler
{
	public:
		InputHandler();

		~InputHandler();

		enum keyStates
		{
			up = 0,
			down,
			released,
			pressed
		};

		std::vector<int> handleInput();

	private:
		std::vector<bool> prevKeys;
};

