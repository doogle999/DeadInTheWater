#pragma once

#include "Properties.h"
#include "Entity.h"
#include "Field.h"
#include "Fields.h"

class Entity;

class TranslationIncrementer : public Field
{
	public:
		TranslationIncrementer();

		~TranslationIncrementer();

		virtual void update();

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;
};

