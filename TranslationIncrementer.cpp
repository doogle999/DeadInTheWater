#include "TranslationIncrementer.h"

TranslationIncrementer::TranslationIncrementer() {}

TranslationIncrementer::~TranslationIncrementer() {}

void TranslationIncrementer::update()
{
	for(unsigned int i = 0; i < ei.size(); i++)
	{
		w->entities[ei[i]].AXS(position) = w->entities[ei[i]].AXS(position) + w->entities[ei[i]].AXS(velocity) * Game::getTick();
		w->entities[ei[i]].AXS(velocity) = w->entities[ei[i]].AXS(velocity) + w->entities[ei[i]].AXS(acceleration) * Game::getTick();
	}
}

std::vector<P::Ids> TranslationIncrementer::getNecessaryProperties()
{
	return TranslationIncrementer::necessaryProperties;
}

const std::vector<P::Ids> TranslationIncrementer::necessaryProperties = { P::Ids::position, P::Ids::velocity, P::Ids::acceleration };