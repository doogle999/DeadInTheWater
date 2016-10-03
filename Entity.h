#pragma once

#include <vector>

#include "PVector.h"
#include "UpdateComponent.h"

class UpdateComponent;

class Entity
{
	public:
		Entity(UpdateComponent* u);

		~Entity();

		void updateAll(double t);

		void setPosition(PVector position);
		void setPosition(double positionX, double positionY);
		PVector getPosition() const;

		void setVelocity(PVector velocity);
		void setVelocity(double velocityX, double velocityY);
		PVector getVelocity() const;

	protected:
		std::vector<UpdateComponent*> updaters;

		PVector position;
		PVector velocity;
};
