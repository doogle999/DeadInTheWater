#pragma once

#include <vector>

#include "Properties.h"
#include "Entity.h"
#include "Field.h"
#include "Controller.h"

class Entity;

class ShipController : public Controller
{
	public:
		ShipController();

		~ShipController();

		virtual void removeEntityIndex(size_t i); // Also deselects if the index that is being removed is selected

		virtual void handleInput();

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;

		int selectedIndex; // The ship that is currently selected, negative if nothing is selected
};