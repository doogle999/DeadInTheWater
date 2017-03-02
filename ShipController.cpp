#include "ShipController.h"

ShipController::ShipController() 
{
	cedeToController = -1;

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
	if(selectedIndex > 0)
	{
		if(KeyMapper::checkFunc(KeyMapper::Func::left))
		{
			w->entities[selectedIndex].AXS(acceleration).c[0] = -10;
		}
		if(KeyMapper::checkFunc(KeyMapper::Func::right))
		{
			w->entities[selectedIndex].AXS(acceleration).c[0] = 10;
		}
		if(KeyMapper::checkFunc(KeyMapper::Func::up))
		{
			w->entities[selectedIndex].AXS(acceleration).c[1] = -10;
		}
		if(KeyMapper::checkFunc(KeyMapper::Func::down))
		{
			w->entities[selectedIndex].AXS(acceleration).c[1] = 10;
		}
	}
}

std::vector<P::Ids> ShipController::getNecessaryProperties()
{
	return ShipController::necessaryProperties;
}

const std::vector<P::Ids> ShipController::necessaryProperties = { P::Ids::position, P::Ids::velocity, P::Ids::acceleration, P::Ids::hitPolygon };