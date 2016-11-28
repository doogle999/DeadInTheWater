#pragma once

#include <vector>

#include "Properties.h"
#include "Entity.h"
#include "Field.h"
#include "Behavior.h"

class Entity;

class Collisions : public Field
{
	public:
		Collisions();
			
		~Collisions();

		virtual void initialize();

		class StopOnCollision : public Behavior
		{
			public:
				StopOnCollision(Collisions& o);

				~StopOnCollision();

				virtual void run(Entity& e);
			
				virtual std::vector<P::Ids> getNecessaryProperties();

			private:
				Collisions& owner;
		};

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;

		bool collision(Entity& e);
};