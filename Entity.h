#pragma once

#include <vector>

#include "PVector.h"
#include "UpdateComponent.h"
#include "RenderComponent.h"

class UpdateComponent;
class RenderComponent;

class Entity
{
	public:
		Entity(std::vector<UpdateComponent*> u, std::vector<RenderComponent*> r);

		void updateAll(double t);

		void renderAll();

		void setPosition(PVector position);
		void setPosition(double positionX, double positionY);
		PVector getPosition() const;

		void setVelocity(PVector velocity);
		void setVelocity(double velocityX, double velocityY);
		PVector getVelocity() const;

		~Entity();

	protected:
		std::vector<UpdateComponent*> updaters;

		std::vector<RenderComponent*> renderers;

		PVector position;
		PVector velocity;
};
