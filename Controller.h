#pragma once

#include <vector>

#include "KeyMapper.h"
#include "Field.h"
#include "Fields.h"

class Controller : public Field // Interface for a controller that can cede control
{
	public:
		virtual void handleInput() = 0;

		int checkCedeToController()
		{
			if(cedeToController >= 0)
			{
				int temp = cedeToController;
				cedeToController = -1;
				return temp;
			}
			else
			{
				return -1;
			}
		}

	private:
		int cedeToController; // This controller is broadcasting to cede its control to a different controller
};