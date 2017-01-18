#include "Field.h"

void Field::setWorld(World* w)
{
	this->w = w;
}

void Field::addEntityIndex(size_t i)
{
	ei.push_back(i);
}
void Field::removeEntityIndex(size_t i)
{
	ei.erase(std::remove(ei.begin(), ei.end(), i), ei.end());
}

void Field::input() {}
void Field::update() {}
void Field::render() {}