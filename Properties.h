#pragma once

#include "SFML\Graphics\Color.hpp"

#include <map>
#include <string>

#include "PVector.h"

#define ADD_TYPE(NAME, TYPE) typedef TYPE TYPE_ ## NAME;
#define COMMA ,

struct P
{
	enum Ids // Used for access
	{
		position,
		velocity,
		acceleration,
		orientation,
		orientationVelocity,
		reloadTime,
		timeoutTime,
	};

	ADD_TYPE(position, PVector<double COMMA 2>)
	ADD_TYPE(velocity, PVector<double COMMA 2>)
	ADD_TYPE(acceleration, PVector<double COMMA 2>)
	ADD_TYPE(orientation, double) // Radians, 0 to 2PI, measured from positive x-axis
	ADD_TYPE(orientationVelocity, double)
	ADD_TYPE(reloadTime, double)
	ADD_TYPE(timeoutTime, double)

	static const std::map<P::Ids, size_t> Sizes; // Used in Entity memory allocation
	static const std::map<std::string, P::Ids> Names; // Used in decoding and recoding XML
};

#undef ADD_TYPE
#undef COMMA