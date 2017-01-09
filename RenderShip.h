#pragma once

#include "SFML/Graphics.hpp"

#include "Behavior.h"
#include "Entity.h"

class RenderShip : public Behavior
{
	public:
		RenderShip();

		~RenderShip();

		virtual void run(Entity& e);

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;
};