#pragma once

#include "RenderComponent.h"

class DrawCircleRC : public RenderComponent
{
	public:
		DrawCircleRC();

		virtual void render(Entity& e, sf::RenderWindow* w);

		~DrawCircleRC();
};

