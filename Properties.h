#pragma once

#include "SFML\Graphics\Color.hpp"

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
		xAcceleration,
		yAcceleration,
		selected,
		radius,
		mass,
		reloadTime,
		color,
		renderRadius,
		timeoutTime
	};

	ADD_TYPE(xPosition, double)
	ADD_TYPE(yPosition, double)
	ADD_TYPE(xVelocity, double)
	ADD_TYPE(yVelocity, double)
	ADD_TYPE(xAcceleration, double)
	ADD_TYPE(yAcceleration, double)
	ADD_TYPE(selected, bool)
	ADD_TYPE(radius, double)
	ADD_TYPE(mass, double)
	ADD_TYPE(reloadTime, double)
	ADD_TYPE(color, sf::Color)
	ADD_TYPE(renderRadius, double)
	ADD_TYPE(timeoutTime, double)

	static const std::map<P::Ids, size_t> Sizes; // Used in Entity memory allocation
	static const std::map<std::string, P::Ids> Names; // Used in decoding and recoding XML
};

#undef ADD_TYPE