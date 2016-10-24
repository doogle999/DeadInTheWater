#include "Entity.h"

Entity::Entity(InputComponent* i, UpdateComponent* u, RenderComponent* r)
{
	inputer = i;
	updater = u;
	renderer = r;
}

InputComponent* Entity::getInputComponent() { return inputer; }
UpdateComponent* Entity::getUpdateComponent() { return updater;  }
RenderComponent* Entity::getRenderComponent() { return renderer; }

double Entity::getPositionX() { return positionX; }
void Entity::setPositionX(double px) { positionX = px; }
double Entity::getPositionY() { return positionY; }
void Entity::setPositionY(double py) { positionY = py; }

double Entity::getVelocityX() { return velocityX; }
void Entity::setVelocityX(double vx) { velocityX = vx; }
double Entity::getVelocityY() { return velocityY; }
void Entity::setVelocityY(double vy) { velocityY = vy; }

Entity::~Entity() {}
