#pragma once

#include "SFML/Window/Mouse.hpp"

#include <vector>

#include "PVector.h"

class Cursor
{
	public:
		enum Func
		{
			leftClick,
			rightClick
		};

		static bool checkFunc(Func f);
		static PVector<int, 2> checkCursorLocation();


	private:
		static std::vector<sf::Mouse::Button> BUTTON_FUNC_MAP; // Maps func to keys, added layer of mapping on order to allow keys to be switched, indexes are Funcs, keys are values
};
