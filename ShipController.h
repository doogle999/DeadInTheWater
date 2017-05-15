#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <math.h>

#include "Entity.h"
#include "Field.h"
#include "Controller.h"
#include "Camera2D.h"

class Entity;

class ShipController : public Controller
{
	public:
		ShipController();

		~ShipController();

		virtual void removeEntityIndex(size_t i); // Also deselects if the index that is being removed is selected

		virtual void handleInput();

		virtual std::vector<Attribute::Ids> getNecessaryProperties();

	private:
		static const std::vector<Attribute::Ids> necessaryProperties;

		int selectedIndex; // The ship that is currently selected, negative if nothing is selected, of w->entities not ei
		bool inMovementMode; 
};