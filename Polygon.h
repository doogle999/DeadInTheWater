#pragma once

#include <vector>
#include <algorithm>

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
		
		PVector<T, 2>
		bool pointInside(PVector<T, 2> p) const; // Relative to top left, so we need to orient the point relative to that origin before using this
		std::vector<Polygon<T>> monotonize() const; // Creates a monotone polygon breakdown of this polygon

		std::vector<PVector<T, 2>> points;
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
	points = p.points;

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

template <typename T>
std::vector<Polygon<T>> Polygon<T>::monotonize() const
{
	if(points.size() > 3)
	{
		std::vector<std::pair<unsigned int, T>> pointsSortedByY;
		pointsSortedByY.resize(points.size());
		for(unsigned int i = 0; i < pointsSortedByY.size(); i++)
		{
			pointsSortedByY[i] = std::make_pair(i, points[i].c[1]);
		}
		std::sort(pointsSortedByY.begin(), pointsSortedByY.end(), [](PVector<T, 2> const& a, std::pair<unsigned int, T> const& b) { return a.second < b.second; });

		std::vector<Polygon<T>> monotonizedPolygons;
		std::vector<Polygon<T>> currentPolygons;

		for(unsigned int p = 0; p < pointsSortedByY.size(); p++) // Loop the nodes
		{
			if(points[(p.first - 1) % points.size()].c[1] == points[p.first] || points[(p.first + 1) % points.size()].c[1] == points[p.first].c[1]) // One or both neighbors are at the same height, no possible new shape
			{
				
			}
			else
			{
				if() // Both neighbors are above, starting one of the polys
				{
					currentPolygons.push_back();
				}

				else if() // Both neighbors are below, closing one of the polys
				{

				}

				else // One neighbor is above the other is below
				{

				}
			}

			for(unsigned int i = 0, j = points.size() - 1; i < points.size(); j = i++) // Loop the edges
			{
				if(points[i].c[1] == p.c[1]) {} // Skip when the "after" point is on the line, it will be picked up next loop, parallel edges will thus be counted as 0
				else if(points[j].c[1] == p.c[1]) // The "before" point is on the line but the other isn't, the vertex will thus be counted as 1, and it will only be counted once
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
	}
}