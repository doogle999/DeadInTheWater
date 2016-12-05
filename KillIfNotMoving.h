#pragma once

#include "Behavior.h"
#include "Entity.h"

class KillIfNotMoving : public Behavior
{
	public:
		KillIfNotMoving();

		~KillIfNotMoving();

		virtual void run(Entity& e);

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;
};