#pragma once

#include "SFML\Graphics\Color.hpp"

#include <map>
#include <string>

#include "Point.h"

#define ADD_TYPE(NAME, TYPE) typedef TYPE TYPE_ ## NAME;

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

	ADD_TYPE(position, Point)
	ADD_TYPE(velocity, Point)
	ADD_TYPE(acceleration, Point)
	ADD_TYPE(orientation, double) // Radians, 0 to 2PI, measured from positive x-axis
	ADD_TYPE(orientationVelocity, double)
	ADD_TYPE(reloadTime, double)
	ADD_TYPE(timeoutTime, double)

	static const std::map<P::Ids, size_t> Sizes; // Used in Entity memory allocation
	static const std::map<std::string, P::Ids> Names; // Used in decoding and recoding XML
};

#undef ADD_TYPE