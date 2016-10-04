#pragma once

#include "UpdateComponent.h"

class ConstantVelocityUC : public UpdateComponent
{
	public:
		ConstantVelocityUC();

		virtual void update(Entity& e, double t);

		~ConstantVelocityUC();
};

