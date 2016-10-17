#pragma once

#include "UpdateComponent.h"

template <typename T> class ConstantVelocityUC : public UpdateComponent<T>
{
	public:
		ConstantVelocityUC() {};

		virtual void update(T& e, double t)
		{
			e.setPosition(e.getPosition() + e.getVelocity());
		}

		~ConstantVelocityUC() {};
};

