#pragma once

#include "Behavior.h"
#include "Entity.h"

class IncrementPosition : public Behavior
{
	public:
		IncrementPosition();

		~IncrementPosition();

		virtual void run(Entity& e);

		virtual std::vector<P::Ids> getNecessaryProperties();
		
	private:
		static const std::vector<P::Ids> necessaryProperties;
};