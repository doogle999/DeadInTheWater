#pragma once

#include <vector>

#include "Point.h"

class Polygon
{
	public:
		Polygon();
		Polygon(std::vector<Point> p);

		~Polygon();

		std::vector<Point> points; // Points go clockwise, last attaches back to first but is not the same point
};