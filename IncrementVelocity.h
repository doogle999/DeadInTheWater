#pragma once

#include "Behavior.h"
#include "Entity.h"

class IncrementVelocity : public Behavior
{
	public:
		IncrementVelocity();

		~IncrementVelocity();

		virtual void run(Entity& e);

		virtual std::vector<P::Ids> getNecessaryProperties();
		
	private:
		static const std::vector<P::Ids> necessaryProperties;
};