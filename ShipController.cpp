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
		if(eve == SFMLInputHandler::Eve::select) // Check if there are any ships selected
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
				if(selectedIndex != -1)
				{
					Entity& shipPointer = w->entities[selectedIndex];
					shipPointer.AXS(Translation).velocity = dynamic_cast<Camera2D*>(w->fields[Fields::Ids::Id_Camera2D])->screenPosToGamePos(inputPointer->getMousePosRelWin().convert<double>()) - shipPointer.AXS(Translation).position;
				}
				else
				{
					selectedIndex = -1;
				}
			}
		}

		eve = inputPointer->popEve();
	}

	if(selectedIndex >= 0) // Ship movement controls
	{
		/*
		Entity& shipPointer = w->entities[selectedIndex];
		PVector<double, 2> shipForward;
		shipForward.setMagAngle(1, shipPointer.AXS(Orientation).theta);
		PVector<double, 2> shipHorizontal;
		shipHorizontal.setMagAngle(1, shipPointer.AXS(Orientation).theta + M_PI / 2);

		shipPointer.AXS(Orientation).alpha = (1.0 / 5.0) * pow(shipPointer.AXS(Translation).velocity.mag(), 2) * (inputPointer->checkFunc(SFMLInputHandler::Func::right) - inputPointer->checkFunc(SFMLInputHandler::Func::left));
		shipPointer.AXS(Orientation).omega = (shipPointer.AXS(Orientation).omega / pow(1.1, abs(shipPointer.AXS(Orientation).omega)));

		shipPointer.AXS(Translation).acceleration.setMagAngle(5 * (inputPointer->checkFunc(SFMLInputHandler::Func::up) - inputPointer->checkFunc(SFMLInputHandler::Func::down)), shipPointer.AXS(Orientation).theta);
		shipPointer.AXS(Translation).velocity = shipForward * shipForward.dot(shipPointer.AXS(Translation).velocity);
		shipPointer.AXS(Translation).velocity = (shipPointer.AXS(Translation).velocity * (1.0 / pow(1.1, shipPointer.AXS(Translation).velocity.mag())));
		*/
	}

	Camera2D* cameraPointer = dynamic_cast<Camera2D*>(w->fields[Fields::Ids::Id_Camera2D]); // Move the camera 

	cameraPointer->cameraControls({ SFMLInputHandler::Func::leftSecondary, SFMLInputHandler::Func::rightSecondary, SFMLInputHandler::Func::upSecondary, SFMLInputHandler::Func::downSecondary, SFMLInputHandler::Func::zoomIn, SFMLInputHandler::Func::zoomOut });
}

std::vector<Attribute::Ids> ShipController::getNecessaryProperties()
{
	return ShipController::necessaryProperties;
}

const std::vector<Attribute::Ids> ShipController::necessaryProperties = { Attribute::Ids::Translation, Attribute::Ids::Orientation, Attribute::Ids::HitPolygon };