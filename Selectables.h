#pragma once

#include <vector>

#include "Properties.h"
#include "Entity.h"
#include "Field.h"
#include "Behavior.h"

class Entity;

class Selectables : public Field
{
	public:
		Selectables();

		~Selectables();

		class SelectOnClick : public Behavior
		{
			public:
				SelectOnClick(Selectables& o);

				~SelectOnClick();

				virtual void run(Entity& e);

				virtual std::vector<P::Ids> getNecessaryProperties();

			private:
				Selectables& owner;
		};

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;
};