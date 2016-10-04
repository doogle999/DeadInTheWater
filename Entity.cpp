#include "Entity.h"

Entity::Entity(std::vector<UpdateComponent*> u)
{
	updaters = u;
}

Entity::~Entity()
{

}

void Entity::updateAll(double t)
{
	for(int i = 0; i < updaters.size(); i++)
	{
		updaters[i]->update((*this), t);
	}
}

void Entity::setPosition(PVector position) { this->position = position; }
void Entity::setPosition(double positionX, double positionY) { this->position.setXY(positionX, positionY); }
PVector Entity::getPosition() const { return this->position; }

void Entity::setVelocity(PVector velocity) { this->velocity = velocity; }
void Entity::setVelocity(double velocityX, double velocityY) { this->velocity.setXY(velocityX, velocityY); }
PVector Entity::getVelocity() const { return this->velocity; }
