#pragma once

#include <vector>

#include "PVector.h"

template <typename T>
class Polygon
{
	public:
		Polygon();
		Polygon(std::vector<PVector<T, 2>> p);
		Polygon(const Polygon<T>& p);

		Polygon& operator=(const Polygon<T>& p);

		~Polygon();

		bool pointInside(PVector<T, 2> p) const; // Relative to top left, so we need to orient the point relative to that origin before using this

		std::vector<PVector<T, 2>> points; // Points go clockwise, last attaches back to first but is not the same point
};

template <typename T>
Polygon<T>::Polygon() {}
template <typename T>
Polygon<T>::Polygon(std::vector<PVector<T, 2>> p) : points(p) {}
template <typename T>
Polygon<T>::Polygon(const Polygon<T>& p) 
{
	points = p.points;
}

template<typename T>
Polygon<T>& Polygon<T>::operator=(const Polygon<T>& p)
{
	points.reserve(1);

	return *this;
}

template <typename T>
Polygon<T>::~Polygon() {}

template <typename T>
bool Polygon<T>::pointInside(PVector<T, 2> p) const
{
	if(points.size() >= 3) // Minimum is triangle for a point to be inside
	{
		bool result = false;
		for(unsigned int i = 0, j = points.size() - 1; i < points.size(); j = i++) // Loop the edges
		{
			if(points[i].c[1] == p.c[1]) {}
			else if(points[j].c[1] == p.c[1]) // The "before" point is on the line but the other isn't, also gets rid of parallel edge cases
			{
				if(p.c[0] < points[j].c[0]) // Intersection
				{
					if((points[(j - 1) % points.size()].c[1] > p.c[1]) != (points[i].c[1] > p.c[1])) // The two edges are on opposite sides of the vertex we are going over so we are changing from out to in or in to out
					{
						result = !result;
					}
				}
			}
			else if((points[j].c[1] > p.c[1]) != (points[i].c[1] > p.c[1])) // One is above and one is below, we know we could intersect
			{
				if(p.c[0] < (points[i].c[0] - points[j].c[0]) / (points[i].c[1] - points[j].c[1]) * (-points[j].c[1] + p.c[1]) + points[j].c[0]) // If px < run/rise of edge * height of point in line + jx, intersection
				{
					result = !result;
				}
			}
		}
		return result;
	}
	else
	{
		return false;
	}
}