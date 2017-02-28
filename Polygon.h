#pragma once

#include <vector>

#include "PVector.h"

template <typename T>
class Polygon
{
	public:
		Polygon();
		Polygon(std::vector<PVector<T, 2>> p);

		~Polygon();

		std::vector<PVector<T, 2>> points; // Points go clockwise, last attaches back to first but is not the same point
};

template <typename T>
Polygon<T>::Polygon() {}
template <typename T>
Polygon<T>::Polygon(std::vector<PVector<T, 2>> p) : points(p) {}

template <typename T>
Polygon<T>::~Polygon() {}
