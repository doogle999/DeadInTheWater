#include "KeyMapper.h"

bool KeyMapper::checkFunc(Func f) // Checks if the key associated with a funcionality is down (true if down, false if up)
{
	return sf::Keyboard::isKeyPressed(KEY_FUNC_MAP[f]);
};

std::vector<sf::Keyboard::Key> KeyMapper::KEY_FUNC_MAP = {};
