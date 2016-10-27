#include "Entity.h"

Entity::Entity(std::vector<P> p)
{
	for(unsigned int i = 0; i < p.size(); i++)
	{
		ps.push_back(p[i]);

		switch (p[i] / 100)
		{
		case 0: pDouble[p[i] % 100] = 0.0;
			break;

		case 1: pInt[p[i] % 100] = 0;
			break;

		default: ps.pop_back();
			break;
		}
	}
}

bool Entity::compatible(Behavior* b)
{
	std::vector<P> pn = b->getNecessaryProperties();

	for(unsigned int i = 0; i < pn.size(); i++)
	{
		if (std::find(ps.begin(), ps.end(), pn[i]) == ps.end())
		{
			return false;
		}
	}
	return true;
}

void Entity::input()
{
	for(unsigned int i = 0; i < inputers.size(); i++)
	{
		inputers[i]->run(*this);
	}
}
void Entity::update()
{
	for (unsigned int i = 0; i < updaters.size(); i++)
	{
		updaters[i]->run(*this);
	}
}
void Entity::render()
{
	for (unsigned int i = 0; i < renderers.size(); i++)
	{
		renderers[i]->run(*this);
	}
}

bool Entity::addInputer(Behavior* b)
{
	if(compatible(b))
	{
		inputers.push_back(b);
		return true;
	}
	else
	{
		return false;
	}
}
bool Entity::addUpdater(Behavior* b)
{
	if(compatible(b))
	{
		updaters.push_back(b);
		return true;
	}
	else
	{
		return false;
	}
}
bool Entity::addRenderer(Behavior* b)
{
	if(compatible(b))
	{
		renderers.push_back(b);
		return true;
	}
	else
	{
		return false;
	}
}

double Entity::getPDouble(int i) { return pDouble.at(i); }
void Entity::setPDouble(int i, double v) { pDouble.at(i) = v; }

int Entity::getPInt(int i) { return pInt.at(i); }
void Entity::setPInt(int i, int v) { pInt.at(i) = v; }

Entity::~Entity() {}
