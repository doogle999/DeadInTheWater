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
	if(selectedIndex >= 0)
	{
		if(KeyMapper::checkFunc(KeyMapper::Func::left))
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[0] = -10;
		}
		else if(KeyMapper::checkFunc(KeyMapper::Func::right))
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[0] = 10;
		}
		else
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[0] = 0;
		}
		if(KeyMapper::checkFunc(KeyMapper::Func::up))
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[1] = -10;
		}
		else if(KeyMapper::checkFunc(KeyMapper::Func::down))
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[1] = 10;
		}
		else
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[1] = 0;
		}
	}
	if(Cursor::checkFunc(Cursor::Func::leftClick))
	{
		bool clickedOnShip = false;

		for(unsigned int i = 0; i < ei.size(); i++)
		{
			if(w->entities[ei[i]].AXS(HitPolygon).hitPolygon.pointInside(dynamic_cast<Camera2D*>(w->fields[Fields::Ids::Id_Camera2D])->screenPosToGamePos(Cursor::checkCursorWindowLocation().convert<double>()) - w->entities[ei[i]].AXS(Translation).position))
			{
				clickedOnShip = true;
				selectedIndex = ei[i];
				break;
			}
		}
		if(!clickedOnShip)
		{
			selectedIndex = -1;
		}
	}
}

std::vector<Attribute::Ids> ShipController::getNecessaryProperties()
{
	return ShipController::necessaryProperties;
}

const std::vector<Attribute::Ids> ShipController::necessaryProperties = { Attribute::Ids::Translation, Attribute::Ids::HitPolygon };