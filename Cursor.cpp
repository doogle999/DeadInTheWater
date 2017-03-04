#include "Cursor.h"

bool Cursor::checkFunc(Func f)
{
	return sf::Mouse::isButtonPressed(BUTTON_FUNC_MAP[f]);
}

PVector<int, 2> Cursor::checkCursorLocation() // With respect to desktop
{
	sf::Vector2i temp = sf::Mouse::getPosition();

	return PVector<int, 2>({ temp.x, temp.y });
}
PVector<int, 2> Cursor::checkCursorWindowLocation() // With respect to window
{
	sf::Vector2i temp = sf::Mouse::getPosition(*Game::window);

	return PVector<int, 2>({ temp.x, temp.y });
}

std::vector<sf::Mouse::Button> Cursor::BUTTON_FUNC_MAP = { sf::Mouse::Button::Left, sf::Mouse::Button::Right };