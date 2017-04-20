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

		bool vertexIsReflex(unsigned int v) const; // Internal angle is greater than 180 degrees, index of vertex
		bool pointInside(PVector<T, 2> p) const; // Relative to top left, so we need to orient the point relative to that origin before using this

		std::vector<Polygon<T>> triangulate() const; // Uses earlcipping to triangulate

		void smooth(); // Smooths big polygons out, parameter is the number of neighbors away points are considered for averaging, 1 is good

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
bool Polygon<T>::vertexIsReflex(unsigned int v) const
{
	if(points.size() > 3) // Minimum is quad for having a reflex vertex
	{
		bool result = false;
		unsigned int loopCount = 0;
		unsigned int i = (v + 1) % points.size();
		unsigned int j = (((int)v - 1) % (int)points.size() + points.size()) % points.size();
		while(loopCount < points.size() - 1)
		{
			if(points[i].c[1] == points[j].c[1]) {} // Parallel edge, ignore
			else if(points[i].c[1] == points[v].c[1]) // The before point is on the line but the other isn't
			{
				if(points[i].c[1] < points[j].c[1])
				{
					if(points[v].c[0] < points[i].c[0]) // Intersection
					{
						result = !result;
					}
				}
			}
			else if(points[j].c[1] == points[v].c[1]) // The after point is on the line but the other isn't
			{
				if(points[j].c[1] < points[i].c[1])
				{
					if(points[v].c[0] < points[j].c[0]) // Intersection
					{
						result = !result;
					}
				}
			}
			else if((points[j].c[1] > points[v].c[1]) != (points[i].c[1] > points[v].c[1])) // One is above and one is below, we know we could intersect
			{
				if(points[v].c[0] < (points[i].c[0] - points[j].c[0]) / (points[i].c[1] - points[j].c[1]) * (-points[j].c[1] + points[v].c[1]) + points[j].c[0]) // If px < run/rise of edge * height of point in line + jx, intersection
				{
					result = !result;
				}
			}

			j = i;
			i = (i + 1) % points.size();
			loopCount++;
		}
		return result;
	}
	else
	{
		return false;
	}
}

template <typename T>
bool Polygon<T>::pointInside(PVector<T, 2> p) const
{
	if(points.size() >= 3) // Minimum is triangle for a point to be inside
	{
		bool result = false;
		for(unsigned int i = 0, j = points.size() - 1; i < points.size(); j = i++) // Loop the edges
		{
			if(points[i].c[1] == points[j].c[1]) {} // Parallel edge, ignore
			else if(points[i].c[1] == p.c[1]) // The before point is on the line but the other isn't
			{
				if(points[i].c[1] < points[j].c[1])
				{
					if(p.c[0] < points[i].c[0]) // Intersection
					{
						result = !result;
					}
				}
			} 
			else if(points[j].c[1] == p.c[1]) // The after point is on the line but the other isn't
			{
				if(points[j].c[1] < points[i].c[1])
				{
					if(p.c[0] < points[j].c[0]) // Intersection
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
std::vector<Polygon<T>> Polygon<T>::triangulate() const
{
	if(points.size() > 3)
	{
		Polygon<T> p;
		
		for(unsigned int i = 0; i < points.size(); i++) // Remove inline points
		{
			unsigned int ib = (((int)i - 1) % (int)points.size() + points.size()) % points.size(); // Point before i
			unsigned int ia = (i + 1) % points.size(); // Point after i

			if((points[i] - points[ib]).angle() != (points[ia] - points[i]).angle())
			{
				p.points.push_back(points[i]);
			}
		}

		std::vector<char> pointStates; // The states of every point, 0 indicates clippable, 1 indicates reflex, 2 indicates convex but unclippable
		pointStates.resize(p.points.size()); // The size will be reduced by 1 after every triangle

		for(unsigned int i = 0; i < p.points.size(); i++) // Identify reflex points
		{
			if(p.vertexIsReflex(i))
			{
				pointStates[i] = 1;
			}
			else
			{
				pointStates[i] = 0;
			}
		}

		for(unsigned int i = 0; i < p.points.size(); i++) // Identify clippable points
		{
			if(pointStates[i] != 1)
			{
				unsigned int ib = (((int)i - 1) % (int)p.points.size() + p.points.size()) % p.points.size(); // Point before i
				unsigned int ia = (i + 1) % p.points.size(); // Point after i

				Polygon tempTriangle({ p.points[i], p.points[ib], p.points[ia] });

				for(unsigned int j = 0; j < p.points.size(); j++) // Check reflex vertices for crossings
				{
					if(pointStates[j] == 1 && j != ib && j != ia)
					{
						if(tempTriangle.pointInside(p.points[j]))
						{
							pointStates[i] = 2;
							break;
						}
					}
				}
			}
		}

		std::vector<Polygon<T>> triangles; // The result

		while(p.points.size() > 3)
		{
			for(unsigned int ear = 0; ear < p.points.size(); ear++) // Find and clip the first ear
			{
				if(pointStates[ear] == 0)
				{
					triangles.push_back({}); // Make the triangle
					triangles.back().points = { p.points[(((int)ear - 1) % (int)p.points.size() + p.points.size()) % p.points.size()], p.points[ear], p.points[(ear + 1) % p.points.size()] };
					p.points.erase(p.points.begin() + ear); // Remove the ear
					pointStates.erase(pointStates.begin() + ear);

					std::array<unsigned int, 2> earN; // Ear neighbors
					if(ear == 0 || ear == p.points.size())
					{
						earN[0] = p.points.size() - 1;
						earN[1] = 0;
					}
					else
					{
						earN[0] = ear - 1;
						earN[1] = ear;
					}
					
					for(unsigned int i = 0; i < 2; i++) // Re-evaluate the neighbor
					{
						if(p.vertexIsReflex(earN[i]))
						{
							pointStates[earN[i]] = 1;
						}
						else
						{
							pointStates[earN[i]] = 0;
						}
					}

					for(unsigned int i = 0; i < 2; i++)
					{
						if(pointStates[earN[i]] != 1)
						{
							unsigned int ib = (((int)earN[i] - 1) % (int)p.points.size() + p.points.size()) % p.points.size(); // Point before i
							unsigned int ia = (earN[i] + 1) % p.points.size(); // Point after i

							Polygon tempTriangle({ p.points[earN[i]], p.points[ib], p.points[ia] });

							for(unsigned int j = 0; j < p.points.size(); j++) // Check reflex vertices for crossings
							{
								if(pointStates[j] == 1 && j != ib && j != ia)
								{
									if(tempTriangle.pointInside(p.points[j]))
									{
										pointStates[earN[i]] = 2;
										break;
									}
								}
							}
						}
					}

					break;
				}
			}
		}

		triangles.push_back(p);
		return triangles;
	}
	else
	{
		return { *this };
	}
}

template <typename T>
void Polygon<T>::smooth()
{
	unsigned int prevPoint = points.size() - 1;
	PVector<T, 2> firstPoint = points[0];

	for(unsigned int i = 0; i < points.size() - 1; i++)
	{
		points[i] = (points[i] + points[prevPoint] + points[i + 1]) * (1.0 / 3.0);

		prevPoint = i;
	}

	points[points.size() - 1] = (firstPoint + points[points.size() - 1] + points[points.size() - 2]) * (1.0 / 3.0);
}