#pragma once

#include "Updateable.h"
#include "PVector.h"

class Ship : public Updateable
{
	public:
		Ship();

		Ship(PVector position, PVector velocity, PVector acceleration, double mass, double dragCoefficient);
		Ship(double positionX, double positionY, double velocityX, double velocityY, double accelerationX, double accelerationY, double mass, double dragCoefficient);

		~Ship();

		virtual void update(double deltaTime);

		void setPose(PVector position, PVector velocity, PVector acceleration);
		void setPose(double positionX, double positionY, double velocityX, double velocityY, double accelerationX, double accelerationY);

		void setPosition(PVector position);
		void setPosition(double positionX, double positionY);
		PVector getPosition() const;

		void setVelocity(PVector velocity);
		void setVelocity(double velocityX, double velocityY);
		PVector getVelocity() const;

		void setAcceleration(PVector acceleration);
		void setAcceleration(double accelerationX, double accelerationY);
		PVector getAcceleration() const;

		void setMass(double mass);
		double getMass() const;

		void Ship::setDragCoefficient(double dragCoefficient);
		double Ship::getDragCoefficient() const;

	private:
		PVector position;
		PVector velocity;
		PVector acceleration;

		double mass;

		double dragCoefficient;
};

