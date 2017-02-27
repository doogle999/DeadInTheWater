#include "ShipController.h"

ShipController::ShipController() 
{
	selectedIndex = -1;
}

ShipController::~ShipController() {}

void ShipController::removeEntityIndex(size_t i)
{
	if(selectedIndex == i)
	{
		selectedIndex = -1;
	}
	Field::removeEntityIndex(i);
}

void ShipController::handleInput()
{
	if(KeyMapper::checkFunc(KeyMapper::Func::left))
	{

	}
}

std::vector<P::Ids> ShipController::getNecessaryProperties()
{
	return ShipController::necessaryProperties;
}

const std::vector<P::Ids> ShipController::necessaryProperties = { P::Ids::position, P::Ids::velocity, P::Ids::acceleration, P::Ids::orientation, P::Ids::orientationVelocity };