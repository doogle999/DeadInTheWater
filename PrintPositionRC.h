#pragma once

#include <iostream>

#include "RenderComponent.h"

class PrintPositionRC : public RenderComponent
{
	public:
		PrintPositionRC();

		virtual void render(Entity& e);

		~PrintPositionRC();
};

