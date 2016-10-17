#pragma once

#include "Entity.h"

template <typename T> class UpdateComponent
{
	public:
		virtual void update(T& e, double t) = 0;
};

