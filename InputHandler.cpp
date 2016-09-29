#include "InputHandler.h"

InputHandler::InputHandler() 
{
	for(int k = sf::Keyboard::Key::A; k != sf::Keyboard::Key::B; k++)
	{
		prevKeys.push_back(false);
	}
}

InputHandler::~InputHandler() {}

std::vector<int> InputHandler::handleInput()
{
	std::vector<int> keys;

	for(int k = sf::Keyboard::Key::A; k != sf::Keyboard::Key::B; k++)
	{
		// USING MATH
		bool keyCheck = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k));

		keys.push_back(static_cast<int>(keyCheck) + 2 * ((static_cast<int>(prevKeys[static_cast<sf::Keyboard::Key>(k)]) + static_cast<int>(keyCheck)) % 2));
		prevKeys[static_cast<sf::Keyboard::Key>(k)] = keyCheck;

		// USING IF
		/*
		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)k))
		{
			if(prevKeys[(sf::Keyboard::Key)k])
			{
				keys[(sf::Keyboard::Key)k] = down;
			}
			else
			{
				keys[(sf::Keyboard::Key)k] = pressed;
			}
		}
		else
		{
			if (prevKeys[(sf::Keyboard::Key)k])
			{
				keys[(sf::Keyboard::Key)k] = released;
			}
			else
			{
				keys[(sf::Keyboard::Key)k] = up;
			}
		}
		*/
	}

	return keys;
}
