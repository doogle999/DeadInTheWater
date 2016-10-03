#pragma once

#include "UpdateComponent.h"

class ConstantVelocityUC : UpdateComponent
{
	public:
		ConstantVelocityUC();

		virtual void update(Entity& e, double t);

		~ConstantVelocityUC();
};

