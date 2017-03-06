#include "Player.h"

Player::Player() 
{
	currentController = Fields::Ids::Id_ShipController;
}

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

std::vector<Attribute::Ids> Player::getNecessaryProperties()
{
	return { };
}
