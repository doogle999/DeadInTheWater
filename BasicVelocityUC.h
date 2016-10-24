#pragma once

#include "UpdateComponent.h"

class BasicVelocityUC : public UpdateComponent
{
	public:
		BasicVelocityUC();

		virtual void update(Entity& e, double t);

		~BasicVelocityUC();
};

