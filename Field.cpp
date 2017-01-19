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

bool Field::compatible(Entity* e)
{
	std::vector<P::Ids> np = getNecessaryProperties();

	for(unsigned int i = 0; i < np.size(); i++)
	{
		if(!e->hasProperty(np[i]))
		{
			return false;
		}
	}
	return true;
}