#pragma once

#include <map>
#include <string>

#define ADD_TYPE(NAME, TYPE) typedef TYPE TYPE_ ## NAME;

struct P
{
	enum Ids // Used for access
	{
		xPosition,
		yPosition,
		xVelocity,
		yVelocity,
		radius
	};

	ADD_TYPE(xPosition, double)
	ADD_TYPE(yPosition, double)
	ADD_TYPE(xVelocity, double)
	ADD_TYPE(yVelocity, double)
	ADD_TYPE(radius, double)

	static const std::map<P::Ids, size_t> Sizes; // Used in Entity memory allocation
	static const std::map<std::string, P::Ids> Names; // Used in decoding and recoding XML
};

#undef ADD_TYPE