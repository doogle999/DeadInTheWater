#include "Ship.h"

Ship::Ship() {}

Ship::Ship(PVector position, PVector velocity, PVector acceleration, double mass)
{
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->mass = mass;
}

Ship::~Ship() {}

void Ship::update(double deltaTime) 
{
	position = position + (velocity * (deltaTime / 1000));

	velocity = velocity + (acceleration * (deltaTime / 1000));

	acceleration = velocity * (velocity.magnitude() * dragCoefficient * crossSectionalArea * (-1 / mass));
}

void Ship::setPose(PVector position, PVector velocity, PVector acceleration)
{
	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
}
void Ship::setPose(double positionX, double positionY, double velocityX, double velocityY, double accelerationX, double accelerationY)
{
	position.setXY(positionX, positionY);
	velocity.setXY(velocityX, velocityY);
	acceleration.setXY(accelerationX, accelerationY);
}

void Ship::setPosition(PVector position) { this->position = position; }
void Ship::setPosition(double positionX, double positionY) { this->position.setXY(positionX, positionY); }
PVector Ship::getPosition() const { return this->position; }

void Ship::setVelocity(PVector velocity) { this->velocity = velocity; }
void Ship::setVelocity(double velocityX, double velocityY) { this->velocity.setXY(velocityX, velocityY); }
PVector Ship::getVelocity() const { return this->velocity; }

void Ship::setAcceleration(PVector acceleration) { this->acceleration = acceleration; }
void Ship::setAcceleration(double accelerationX, double accelerationY) { this->acceleration.setXY(accelerationX, accelerationY); }
PVector Ship::getAcceleration() const { return this->acceleration; }

void Ship::setMass(double mass) { this->mass = mass; }
double Ship::getMass() const { return this->mass; }

void Ship::setDragCoefficient(double dragCoefficient) { this->dragCoefficient = dragCoefficient; }
double Ship::getDragCoefficient() const { return this->dragCoefficient; }
void Ship::setCrossSectionalArea(double crossSectionalArea) { this->crossSectionalArea = crossSectionalArea; }
double Ship::setCrossSectionalArea() const { return this->crossSectionalArea; }