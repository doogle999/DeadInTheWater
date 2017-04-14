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
/*
template <typename T>
std::vector<Polygon<T>> Polygon<T>::monotonize() const
{
	if(points.size() > 3)
	{
		std::vector<std::vector<PVector<T, 2>>> ; // 
		pointsInbetween.resize(points.size()); // Inbetween points attributed to lower neighbor in index
		std::vector<unsigned int> linkPoints;
		std::fill(pointsExtBreak.begin(), pointsExtBreak.end(), false);

		for(unsigned int v = 0; v < points.size(); v++)
		{
			if(points[(v - 1) % points.size()].c[1] == points[v].c[1] && points[(v + 1) % points.size()].c[1] == points[v].c[1]) {} // Both neighbors are on level
			else if((points[(v - 1) % points.size()].c[1] > points[v].c[1]) == (points[(v + 1) % points.size()].c[1] > points[v].c[1]) || (points[(v - 1) % points.size()].c[1] < points[v].c[1]) == (points[(v + 1) % points.size()].c[1] < points[v].c[1])) // Both neighbors are above or below or just one is on level
			{
				if(vertexIsReflex(v)) // The point is a reflex vertex
				{
					std::vector<std::tuple<unsigned int, unsigned int, PVector<T, 2>, double>> intersections; // First vertex, second vertex, intersection, distance between points 0 to 1
					for(unsigned int i = 0, j = points.size() - 1; i < points.size(); j = i++) // Find the two points of intersection on either side of the point
					{
						if(v == i || v == j) {} // The vertex is one of the points, ignore
						else if(points[i].c[1] == points[v].c[1]) {} // The "after" point is on the line, we'll get to this next loop
						else if(points[j].c[1] == points[v].c[1]) // The "before" point is on the line but the other isn't, also gets rid of parallel edge cases
						{
							intersections.push_back(std::make_tuple(j, i, points[j], ));
						}
						else if((points[j].c[1] > points[v].c[1]) != (points[i].c[1] > points[v].c[1])) // One is above and one is below, we know we could intersect
						{
							intersections.push_back(std::make_tuple(j, i, { (points[i].c[0] - points[j].c[0]) / (points[i].c[1] - points[j].c[1]) * (-points[j].c[1] + points[v].c[1]) + points[j].c[0], points[v].c[1] });
						}
					}

					// Sort the intersections, only the nearest two the left and right are counted
					std::sort(intersections.begin(), intersections.end(), [](std::tuple<unsigned int, unsigned int, PVector<T, 2>> const& a, std::tuple<unsigned int, unsigned int, PVector<T, 2>> const& b)
					{ return a.get<PVector<T, 2>(2).c[0] < b.get<PVector<T, 2>(2).c[0]});


					for(unsigned int i = 0; i < intersections.size(); i++)
					{
						if()
					}
				}
			}
		}
		std::sort(sortedPoints.begin(), sortedPoints.end(), [points](std::vector<unsigned int> const& a, std::vector<unsigned int> const& b) { return points[a[0]].c[1] < points[b[0]].c[1]; });
		for(unsigned int i = 0; i < sortedPoints.size(); i++)
		{
			std::sort(sortedPoints[i].begin(), sortedPoints[i].end(), [points](unsigned int const& a, unsigned int const& b) { return points[a].c[0] < points[b].c[0]; });
		}

		std::vector<Polygon<T>> monotonizedPolygons;
		std::vector<Polygon<T>> currentPolygons;

		for(unsigned int p = 0; p < sortedPoints.size(); p++) // Loop the nodes
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
		}
	}
}
*/

template <typename T>
std::vector<Polygon<T>> Polygon<T>::triangulate() const
{
	if(points.size() > 3)
	{
		std::vector<PVector<T, 2>> p;
		std::map<unsigned int, unsigned int> pMap; // Maps p index to points index
		for(unsigned int i = 0; i < points.size(); i++) // Remove inline points
		{
			unsigned int ib = (((int)i - 1) % (int)points.size() + points.size()) % points.size(); // Point before i
			unsigned int ia = (i + 1) % points.size(); // Point after i

			if((points[i] - points[ib]).angle() != (points[ia] - points[i]).angle())
			{
				p.push_back(points[i]);
				pMap[p.size() - 1] = i;
			}
		}

		std::vector<char> pointStates; // The states of every point, 0 indicates clippable, 1 indicates reflex, 2 indicates convex but unclippable
		pointStates.resize(p.size()); // The size will be reduced by 1 after every triangle

		for(unsigned int i = 0; i < p.size(); i++) // Identify reflex points
		{
			if(vertexIsReflex(pMap[i]))
			{
				pointStates[i] = 1;
			}
			else
			{
				pointStates[i] = 0;
			}
		}

		for(unsigned int i = 0; i < p.size(); i++) // Identify clippable points
		{
			if(pointStates[i] != 1)
			{
				unsigned int ib = (((int)i - 1) % (int)p.size() + p.size()) % p.size(); // Point before i
				unsigned int ia = (i + 1) % p.size(); // Point after i

				Polygon tempTriangle({ p[i], p[ib], p[ia] });

				for(unsigned int j = 0; j < p.size(); j++) // Check reflex vertices for crossings
				{
					if(pointStates[j] == 1 && j != ib && j != ia)
					{
						if(tempTriangle.pointInside(p[j]))
						{
							pointStates[i] = 2;
							break;
						}
					}
				}
			}
		}

		std::vector<Polygon<T>> triangles; // The result

		while(p.size() > 3)
		{
			for(unsigned int ear = 0; ear < p.size(); ear++) // Find and clip the first ear
			{
				if(pointStates[ear] == 0)
				{
					triangles.push_back({}); // Make the triangle
					triangles.back().points = { p[(((int)ear - 1) % (int)p.size() + p.size()) % p.size()], p[ear], p[(ear + 1) % p.size()] };
					p.erase(p.begin() + ear); // Remove the ear
					pointStates.erase(pointStates.begin() + ear);

					std::array<unsigned int, 2> earN; // Ear neighbors
					if(ear == 0 || ear == p.size())
					{
						earN[0] = p.size() - 1;
						earN[1] = 0;
					}
					else
					{
						earN[0] = ear - 1;
						earN[1] = ear;
					}
					
					for(unsigned int i = 0; i < 2; i++) // Re-evaluate the neighbor
					{
						if(vertexIsReflex(pMap[earN[i]]))
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
							unsigned int ib = (((int)earN[i] - 1) % (int)p.size() + p.size()) % p.size(); // Point before i
							unsigned int ia = (earN[i] + 1) % p.size(); // Point after i

							Polygon tempTriangle({ p[earN[i]], p[ib], p[ia] });

							for(unsigned int j = 0; j < p.size(); j++) // Check reflex vertices for crossings
							{
								if(pointStates[j] == 1 && j != ib && j != ia)
								{
									if(tempTriangle.pointInside(p[j]))
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