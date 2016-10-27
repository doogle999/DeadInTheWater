#pragma once

#include <vector>

#include "InputComponent.h"
#include "UpdateComponent.h"
#include "RenderComponent.h"

class InputComponent;
class UpdateComponent;
class RenderComponent;

class Entity
{
	public:
		Entity(InputComponent* i, UpdateComponent* u, RenderComponent* r);

		InputComponent* getInputComponent();
		UpdateComponent* getUpdateComponent();
		RenderComponent* getRenderComponent();

		double getPositionX();
		void setPositionX(double px);
		double getPositionY();
		void setPositionY(double py);

		double getVelocityX();
		void setVelocityX(double vx);
		double getVelocityY();
		void setVelocityY(double vy);

		~Entity();

	private:
		InputComponent* inputer;
		UpdateComponent* updater;
		RenderComponent* renderer;

		double positionX;
		double positionY;

		double velocityX;
		double velocityY;
};
