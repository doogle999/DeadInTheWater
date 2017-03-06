#include "TranslationIncrementer.h"

TranslationIncrementer::TranslationIncrementer() {}

TranslationIncrementer::~TranslationIncrementer() {}

void TranslationIncrementer::update()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		A::Translation& t = w->entities[ei[i]].AXS(Translation);

		t.position = t.position +t.velocity * Game::getTick();
		t.velocity = t.velocity + t.acceleration * Game::getTick();
	}
}

std::vector<Attribute::Ids> TranslationIncrementer::getNecessaryProperties()
{
	return TranslationIncrementer::necessaryProperties;
}

const std::vector<Attribute::Ids> TranslationIncrementer::necessaryProperties = { Attribute::Ids::Translation };