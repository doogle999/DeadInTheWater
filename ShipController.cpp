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
	SFMLInputHandler* inputPointer = dynamic_cast<SFMLInputHandler*>(w->fields[Fields::Ids::Id_SFMLInputHandler]);

	int eve = inputPointer->popEve();

	while(eve >= 0)
	{
		if(eve == SFMLInputHandler::Eve::select)
		{
			bool clickedOnShip = false;

			for(unsigned int i = 0; i < ei.size(); i++)
			{
				if(w->entities[ei[i]].AXS(HitPolygon).hitPolygon.pointInside(dynamic_cast<Camera2D*>(w->fields[Fields::Ids::Id_Camera2D])->screenPosToGamePos(inputPointer->getMousePosRelWin().convert<double>()) - w->entities[ei[i]].AXS(Translation).position))
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

		eve = inputPointer->popEve();
	}

	if(selectedIndex >= 0)
	{
		if(inputPointer->checkFunc(SFMLInputHandler::Func::left))
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[0] = -10;
		}
		else if(inputPointer->checkFunc(SFMLInputHandler::Func::right))
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[0] = 10;
		}
		else
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[0] = 0;
		}
		if(inputPointer->checkFunc(SFMLInputHandler::Func::up))
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[1] = -10;
		}
		else if(inputPointer->checkFunc(SFMLInputHandler::Func::down))
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[1] = 10;
		}
		else
		{
			w->entities[selectedIndex].AXS(Translation).acceleration.c[1] = 0;
		}
	}
	
	
	
}

std::vector<Attribute::Ids> ShipController::getNecessaryProperties()
{
	return ShipController::necessaryProperties;
}

const std::vector<Attribute::Ids> ShipController::necessaryProperties = { Attribute::Ids::Translation, Attribute::Ids::HitPolygon };