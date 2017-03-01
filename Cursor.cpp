#include "Cursor.h"

bool Cursor::checkFunc(Func f)
{
	return sf::Mouse::isButtonPressed(BUTTON_FUNC_MAP[f]);
}

PVector<int, 2> Cursor::checkCursorLocation()
{
	sf::Vector2i temp = sf::Mouse::getPosition();

	return PVector<int, 2>({ temp.x, temp.y });
}

std::vector<sf::Mouse::Button> Cursor::BUTTON_FUNC_MAP = { sf::Mouse::Button::Left, sf::Mouse::Button::Right };