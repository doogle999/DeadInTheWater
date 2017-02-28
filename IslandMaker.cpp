#include "IslandMaker.h"

IslandMaker::IslandMaker() {}

IslandMaker::~IslandMaker() {}

std::vector<Polygon<unsigned int>> IslandMaker::generateIsland(unsigned int sizeFactor, double threshold)
{
	IslandData islandData(sizeFactor, threshold);

	std::vector<std::vector<bool>> unusedOpenEdge; // Locations of land that edge on water or the border
	unusedOpenEdge.resize(sizeFactor * UPSCALE);
	for(unsigned int i = 0; i < unusedOpenEdge.size(); i++)
	{
		unusedOpenEdge[i].resize(unusedOpenEdge.size());
	}
	for(unsigned int i = 0; i < UPSCALE * sizeFactor; i++)
	{
		for(unsigned int j = 0; j < UPSCALE * sizeFactor; j++)
		{
			std::array<bool, 4> temp = islandData.getLocationOpenEdges(j, i);
			if(islandData.boolMap[j][i] && temp[0] + temp[1] + temp[2] + temp[3] > 0)
			{
				unusedOpenEdge[j][i] = true;
			}
			else
			{
				unusedOpenEdge[j][i] = false;
			}
		}
	}

	std::vector<Polygon<unsigned int>> polys; // Grid coordinaes between the squares, 1 larger in both directions than the boolmap

	for(unsigned int j = 0; j < UPSCALE * sizeFactor; j++) // Y position
	{
		for(unsigned int i = 0; i < UPSCALE * sizeFactor; i++) // X position
		{
			if(unusedOpenEdge[i][j])
			{
				Polygon<unsigned int> poly;

				std::vector<std::pair<unsigned int, unsigned int>> possibleLocationsInTwoPolygons; // Locations that are open on two sides and closed on the other two could be part of two polygons, we can't just mark them as used
	
				std::array<bool, 4> temp = islandData.getGridLandLocations(i, j); // If this is an internal lake, we should start 1 down because that's the actual edge
				if(temp[0] + 2 * temp[1] + 4 * temp[2] + 8 * temp[3] == 15)
				{
					poly.points.push_back(PVector<unsigned int, 2>({ i, j + 1 })); // Starting grid coordinates, bottom left of the square found
					poly.points.push_back(PVector<unsigned int, 2>({ i + 1, j + 1 })); // Step to the right, since we know below this square is nothing or water
				}
				else
				{
					poly.points.push_back(PVector<unsigned int, 2>({ i, j })); // Starting grid coordinates, top left of the square found
					poly.points.push_back(PVector<unsigned int, 2>({ i + 1, j })); // Step to the right, since we know above this square is nothing or water
				}

				bool closed = false;
				while(!closed)
				{
					std::array<std::pair<signed char, signed char>, 2> possibleNextPoint;

					std::array<bool, 4> temp = islandData.getGridLandLocations(poly.points[poly.points.size() - 1].c[0], poly.points[poly.points.size() - 1].c[1]);
					unsigned char code = temp[0] + 2 * temp[1] + 4 * temp[2] + 8 * temp[3]; // The surroundings code number: top left determines 0 or 1, top right determines 0 or 2, bottom right determines 0 or 4, bottom left determiens 0 or 8, 16 possible cases

					for(unsigned int k = 0; k < 4; k++) // Set the locations we used to used except if they can possibly be in two polygons
					{
						try 
						{ 
							if(islandData.boolMap.at(poly.points.back().c[0] - (k % 2)).at(poly.points.back().c[1] - (k / 2)))
							{
								std::array<bool, 4> temp = islandData.getLocationOpenEdges(j, i);

								if(abs(temp[0] + temp[2] - temp[1] - temp[3]) == 2)
								{
									if(possibleLocationsInTwoPolygons.erase(
										std::remove(possibleLocationsInTwoPolygons.begin(), 
										possibleLocationsInTwoPolygons.end(), 
										std::make_pair((unsigned int)poly.points.back().c[0] - (k % 2), (unsigned int)poly.points.back().c[1] - (k / 2))),
										possibleLocationsInTwoPolygons.end()) != possibleLocationsInTwoPolygons.end()) // This has been passed over twice, so it can't be in any other polygons, remove it and set it used
									{
										unusedOpenEdge.at(poly.points.back().c[0] - (k % 2)).at(poly.points.back().c[1] - (k / 2)) = false;
									}
									else
									{
										possibleLocationsInTwoPolygons.push_back(std::make_pair(poly.points.back().c[0] - (k % 2), poly.points.back().c[1] - (k / 2)));
									}
								}
								else
								{
									unusedOpenEdge.at(poly.points.back().c[0] - (k % 2)).at(poly.points.back().c[1] - (k / 2)) = false;
								}
							}
						}
						catch(std::out_of_range) {}
					}

					switch(code)
					{
						case 1: 
							possibleNextPoint[0] = std::make_pair(-1, 0);	// #O
							possibleNextPoint[1] = std::make_pair(0, -1);	// OO
							break;
						case 2:
							possibleNextPoint[0] = std::make_pair(1, 0);	// O#
							possibleNextPoint[1] = std::make_pair(0, -1);	// OO
							break;
						case 3:
							possibleNextPoint[0] = std::make_pair(1, 0);	// ##
							possibleNextPoint[1] = std::make_pair(-1, 0);	// OO
							break;
						case 4:
							possibleNextPoint[0] = std::make_pair(1, 0);	// OO
							possibleNextPoint[1] = std::make_pair(0, 1);	// O#
							break;
						case 5:
							if(poly.points[poly.points.size() - 2].c[0] == poly.points[poly.points.size() - 1].c[0] - 1 || poly.points[poly.points.size() - 2].c[1] == poly.points[poly.points.size() - 1].c[1] - 1)
							{
								possibleNextPoint[0] = std::make_pair(-1, 0);	// #O
								possibleNextPoint[1] = std::make_pair(0, -1);	// O#
								unusedOpenEdge[poly.points.back().c[0]][poly.points.back().c[1]] = true;
							}
							else
							{
								possibleNextPoint[0] = std::make_pair(1, 0);	// #O
								possibleNextPoint[1] = std::make_pair(0, 1);	// O#
								unusedOpenEdge[poly.points.back().c[0] - 1][poly.points.back().c[1] - 1] = true;
							}
							break;
						case 6:
							possibleNextPoint[0] = std::make_pair(0, -1);	// O#
							possibleNextPoint[1] = std::make_pair(0, 1);	// O#
							break;
						case 7:
							possibleNextPoint[0] = std::make_pair(-1, 0);	// ##
							possibleNextPoint[1] = std::make_pair(0, 1);	// O#
							break;
						case 8:
							possibleNextPoint[0] = std::make_pair(-1, 0);	// OO
							possibleNextPoint[1] = std::make_pair(0, 1);	// #O
							break;
						case 9:
							possibleNextPoint[0] = std::make_pair(0, 1);	// #O
							possibleNextPoint[1] = std::make_pair(0, -1);	// #O
							break;
						case 10:
							if(poly.points[poly.points.size() - 2].c[0] == poly.points[poly.points.size() - 1].c[0] - 1 || poly.points[poly.points.size() - 2].c[1] == poly.points[poly.points.size() - 1].c[1] + 1)
							{
								possibleNextPoint[0] = std::make_pair(-1, 0);	// O#
								possibleNextPoint[1] = std::make_pair(0, 1);	// #O
								unusedOpenEdge[poly.points.back().c[0]][poly.points.back().c[1] - 1] = true;
							}
							else
							{
								possibleNextPoint[0] = std::make_pair(1, 0);	// O#
								possibleNextPoint[1] = std::make_pair(0, -1);	// #O
								unusedOpenEdge[poly.points.back().c[0]][poly.points.back().c[1] - 1] = true;
							}
							break;
						case 11:
							possibleNextPoint[0] = std::make_pair(1, 0);	// ##
							possibleNextPoint[1] = std::make_pair(0, 1);	// #O
							break;
						case 12:
							possibleNextPoint[0] = std::make_pair(1, 0);	// OO
							possibleNextPoint[1] = std::make_pair(-1, 0);	// ##
							break;
						case 13:
							possibleNextPoint[0] = std::make_pair(1, 0);	// #O
							possibleNextPoint[1] = std::make_pair(0, -1);	// ##
							break;
						case 14:
							possibleNextPoint[0] = std::make_pair(0, -1);	// O#
							possibleNextPoint[1] = std::make_pair(-1, 0);	// ##
							break;
						case 15:
							// Something must have gone wrong...	##
							//										##
							break;
						case 0:
							// Something must have gone wrong...	OO
							//										OO
							break;
					}
					if(poly.points[poly.points.size() - 1].c[0] + possibleNextPoint[0].first == poly.points[poly.points.size() - 2].c[0] &&
						poly.points[poly.points.size() - 1].c[1] + possibleNextPoint[0].second == poly.points[poly.points.size() - 2].c[1]) // Checks which possible next point to use
					{
						poly.points.push_back(PVector<unsigned int, 2>({ poly.points[poly.points.size() - 1].c[0] + possibleNextPoint[1].first, poly.points[poly.points.size() - 1].c[1] + possibleNextPoint[1].second }));
					}
					else
					{
						poly.points.push_back(PVector<unsigned int, 2>({ poly.points[poly.points.size() - 1].c[0] + possibleNextPoint[0].first, poly.points[poly.points.size() - 1].c[1] + possibleNextPoint[0].second }));
					}
					
					if(poly.points[poly.points.size() - 1] == poly.points[0]) // If we are on the same point as the beginning we are done
					{
						closed = true;
						poly.points.pop_back();
					}
				}
				polys.push_back(poly);
			}
		}
	}
	return polys;
}

std::vector<P::Ids> IslandMaker::getNecessaryProperties()
{
	return IslandMaker::necessaryProperties;
};

const std::vector<P::Ids> IslandMaker::necessaryProperties = {};

// 
// NOISE CLASS
//

IslandMaker::Noise::Noise(unsigned int period)
{
	std::iota(permutations.begin(), permutations.end(), 0);
	std::shuffle(permutations.begin(), permutations.end(), Game::rng);

	this->period = period;
}

IslandMaker::Noise::~Noise() {}

double IslandMaker::Noise::getHeight(double x, double y) const
{                            
	x = fmod(x, period);
	y = fmod(y, period);

	int xi = (int)x % period;
	int yi = (int)y % period;

	double xf = x - (int)x;
	double yf = y - (int)y;

	double u = fade(xf);
	double v = fade(yf);

	int aa, ab, ba, bb;
	aa = permutations[(permutations[xi] + yi) % SIZE];
	ab = permutations[(permutations[xi] + increment(yi)) % SIZE];
	ba = permutations[(permutations[increment(xi)] + yi) % SIZE];
	bb = permutations[(permutations[increment(xi)] + increment(yi)) % SIZE];

	double x1, x2;
	x1 = lerp(grad(aa, xf, yf), grad(ba, xf - 1, yf), u);
	x2 = lerp(grad(ab, xf, yf - 1), grad(bb, xf - 1, yf - 1), u);

	return lerp(x1, x2, v);
}

double IslandMaker::Noise::getHeightOctave(double x, double y, unsigned int octaves, double persistence)
{
	double height = 0;
	double frequency = 1;
	double amplitude = 1;
	double maxValue = 0;

	for(unsigned int i = 0; i < octaves; i++)
	{
		height += getHeight(x * frequency, y * frequency) * amplitude;

		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return height / maxValue;
}

int IslandMaker::Noise::increment(int t) const
{
	t++;
	t %= period;

	return t;
}

double IslandMaker::Noise::lerp(double a, double b, double x)
{
	return a + x * (b - a);
}

double IslandMaker::Noise::grad(int hash, double x, double y)
{
	switch(hash & 0x7)
	{
		case 0x0: return  x + y;
		case 0x1: return -x + y;
		case 0x2: return  x - y;
		case 0x3: return -x - y;
		case 0x4: return  x;
		case 0x5: return -x;
		case 0x6: return  y;
		case 0x7: return -y;
		default: return 0;
	}
}

double IslandMaker::Noise::fade(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

// 
// ISLAND DATA CLASS 
//

IslandMaker::IslandData::IslandData(unsigned int sizeFactor, double threshold) : noise(sizeFactor)
{
	this->sizeFactor = sizeFactor;
	this->threshold = threshold;

	maxDistance = sqrt((double)((UPSCALE * sizeFactor / 2) * (UPSCALE * sizeFactor / 2)) + (double)((UPSCALE * sizeFactor / 2) * (UPSCALE * sizeFactor / 2)));

	generateIslandBoolMap();
}

IslandMaker::IslandData::~IslandData() {}

void IslandMaker::IslandData::generateIslandBoolMap()
{
	boolMap.resize(sizeFactor * UPSCALE);

	for(unsigned int i = 0; i < UPSCALE * sizeFactor; i++)
	{
		boolMap[i].resize(sizeFactor * UPSCALE);

		for(unsigned int j = 0; j < UPSCALE * sizeFactor; j++)
		{
			boolMap[i][j] = getLocationHeight(i, j) > threshold;
		}
	}
}

double IslandMaker::IslandData::getLocationHeight(unsigned int x, unsigned int y)
{
	double distance = sqrt((double)((x - UPSCALE * sizeFactor / 2) * (x - UPSCALE * sizeFactor / 2)) + (double)((y - UPSCALE * sizeFactor / 2) * (y - UPSCALE * sizeFactor / 2))); // Distance from center
	double height = -2 * distance / maxDistance + 1;
	height += 0.75 * noise.getHeightOctave((double)x / UPSCALE, (double)y / UPSCALE, 5, 0.2);

	return height;
}

std::array<bool, 4> IslandMaker::IslandData::getGridLandLocations(unsigned int xg, unsigned int yg) 
{
	std::array<bool, 4> locations;

	try
	{
		locations[0] = boolMap.at(xg - 1).at(yg - 1); // Top left
	}
	catch(std::out_of_range)
	{
		locations[0] = false;
	}
	try
	{
		locations[1] = boolMap.at(xg).at(yg - 1); // Top right
	}
	catch(std::out_of_range)
	{
		locations[1] = false;
	}
	try
	{
		locations[2] = boolMap.at(xg).at(yg); // Bottom right
	}
	catch(std::out_of_range)
	{
		locations[2] = false;
	}
	try
	{
		locations[3] = boolMap.at(xg - 1).at(yg); // Bottom left
	}
	catch(std::out_of_range)
	{
		locations[3] = false;
	}
	return locations;
}
bool IslandMaker::IslandData::getLocationIsBorder(unsigned int x, unsigned int y)
{
	return x == 0 || y == 0 || x == boolMap.size() - 1 || y == boolMap.size();
}
std::array<bool, 4> IslandMaker::IslandData::getLocationOpenEdges(unsigned int x, unsigned int y)
{
	std::array<bool, 4> edges;

	try
	{
		edges[0] = (boolMap.at(x - 1).at(y) != boolMap.at(x).at(y)); // Left
	}
	catch(std::out_of_range)
	{
		edges[0] = true;
	}
	try
	{
		edges[1] = (boolMap.at(x).at(y - 1) != boolMap.at(x).at(y)); // Top
	}
	catch(std::out_of_range)
	{
		edges[1] = true;
	}
	try
	{
		edges[2] = (boolMap.at(x + 1).at(y) != boolMap.at(x).at(y)); // Right
	}
	catch(std::out_of_range)
	{
		edges[2] = true;
	}
	try
	{
		edges[3] = (boolMap.at(x).at(y + 1) != boolMap.at(x).at(y)); // Bottom
	}
	catch(std::out_of_range)
	{
		edges[3] = true;
	}
	return edges;
}
unsigned char IslandMaker::IslandData::countLocationOpenEdges(unsigned int x, unsigned int y)
{
	std::array<bool, 4> edges = getLocationOpenEdges(x, y);

	return edges[0] + edges[1] + edges[2] + edges[3];
}
unsigned int IslandMaker::IslandData::countTotalOpenEdges()
{
	unsigned int edgeCount = 0;

	for(unsigned int i = 0; i < UPSCALE * sizeFactor; i++)
	{
		for(unsigned int j = 0; j < UPSCALE * sizeFactor; j++)
		{
			if(boolMap[i][j])
			{
				countLocationOpenEdges(i, j);
			}
		}
	}

	return edgeCount;
}