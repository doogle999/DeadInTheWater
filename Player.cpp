#include "Player.h"

Player::Player() {}

Player::~Player() {}

void Player::input()
{
	Controller* controller = dynamic_cast<Controller*>(w->fields[currentController]);

	controller->handleInput();

	int cede = controller->checkCedeToController();
	if(cede != -1)
	{
		currentController = (Fields::Ids)cede;
	}
}

std::vector<P::Ids> Player::getNecessaryProperties()
{
	return { };
}
