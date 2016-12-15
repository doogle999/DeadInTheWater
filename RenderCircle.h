#pragma once

#include "SFML/Graphics.hpp"

#include "Behavior.h"
#include "Entity.h"

class RenderCircle : public Behavior
{
	public:
		RenderCircle();

		~RenderCircle();

		virtual void run(Entity& e);

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;
};