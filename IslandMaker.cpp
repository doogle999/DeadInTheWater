#include "IslandMaker.h"

IslandMaker::IslandMaker() {}

IslandMaker::~IslandMaker() {}

std::vector<Polygon> IslandMaker::generateIsland(unsigned int sizeFactor, double threshold)
{
	IslandData islandData(sizeFactor, threshold);

	std::vector<std::vector<bool>> usedOpenEdgeMap; // Edges that have already been used
	usedOpenEdgeMap.resize(sizeFactor * UPSCALE);
	for(unsigned int i = 0; i < UPSCALE * sizeFactor; i++)
	{
		usedOpenEdgeMap[i].resize(sizeFactor * UPSCALE);
		for(unsigned int j = 0; j < UPSCALE * sizeFactor; j++)
		{
			usedOpenEdgeMap[i][j] = false;
		}
	}

	std::vector<Polygon> polys; // Grid coordinaes between the squares, 1 larger in both directions than the boolmap

	for(unsigned int i = 0; i < UPSCALE * sizeFactor; i++) // Find the top left most edge
	{
		for(unsigned int j = 0; j < UPSCALE * sizeFactor; j++)
		{
			if(islandData.boolMap[i][j] && !usedOpenEdgeMap[i][j])
			{
				usedOpenEdgeMap[i][j] = true;
				
				Polygon poly;

				poly.points.push_back(Point(i, j)); // Starting grid coordinates, top left of the square found
				poly.points.push_back(Point(i + 1, j + 1)); // Step to the right, since we know above this square is nothing or water

				bool closed = false;
				while(!closed)
				{
					std::array<std::pair<unsigned int, unsigned int>, 2> possibleNextPoint;

					std::array<bool, 4> temp = islandData.getGridLandLocations(poly.points[poly.points.size() - 1].x, poly.points[poly.points.size() - 1].y);
					unsigned char code = temp[0] + 2 * temp[1] + 4 * temp[3] + 8 * temp[4]; // The surroundings code number: top left determines 0 or 1, top right determines 0 or 2, bottom right determines 0 or 4, bottom left determiens 0 or 8, 16 possible cases
					
					switch(code)
					{
						case 1: 
							possibleNextPoint[0] = std::make_pair(-1, 0);	// #O
							possibleNextPoint[1] = std::make_pair(0, 1);	// OO
							break;
						case 2:
							possibleNextPoint[0] = std::make_pair(1, 0);	// O#
							possibleNextPoint[1] = std::make_pair(0, 1);	// OO
							break;
						case 3:
							possibleNextPoint[0] = std::make_pair(1, 0);	// ##
							possibleNextPoint[1] = std::make_pair(-1, 0);	// OO
							break;
						case 4:
							possibleNextPoint[0] = std::make_pair(1, 0);	// OO
							possibleNextPoint[1] = std::make_pair(0, -1);	// O#
							break;
						case 5:
							if(poly.points[poly.points.size() - 2].x == poly.points[poly.points.size() - 1].x - 1 || poly.points[poly.points.size() - 2].y == poly.points[poly.points.size() - 1].y + 1)
							{
								possibleNextPoint[0] = std::make_pair(-1, 0);	// #O
								possibleNextPoint[1] = std::make_pair(0, 1);	// O#
							}
							else
							{
								possibleNextPoint[0] = std::make_pair(1, 0);	// #O
								possibleNextPoint[1] = std::make_pair(0, -1);	// O#
							}
							break;
						case 6:
							possibleNextPoint[0] = std::make_pair(0, -1);	// O#
							possibleNextPoint[1] = std::make_pair(0, 1);	// O#
							break;
						case 7:
							possibleNextPoint[0] = std::make_pair(-1, 0);	// ##
							possibleNextPoint[1] = std::make_pair(0, -1);	// O#
							break;
						case 8:
							possibleNextPoint[0] = std::make_pair(-1, 0);	// OO
							possibleNextPoint[1] = std::make_pair(0, -1);	// #O
							break;
						case 9:
							possibleNextPoint[0] = std::make_pair(0, 1);	// #O
							possibleNextPoint[1] = std::make_pair(0, -1);	// #O
							break;
						case 10:
							if(poly.points[poly.points.size() - 2].x == poly.points[poly.points.size() - 1].x - 1 || poly.points[poly.points.size() - 2].y == poly.points[poly.points.size() - 1].y - 1)
							{
								possibleNextPoint[0] = std::make_pair(-1, 0);	// O#
								possibleNextPoint[1] = std::make_pair(0, -1);	// #O
							}
							else
							{
								possibleNextPoint[0] = std::make_pair(1, 0);	// O#
								possibleNextPoint[1] = std::make_pair(0, 1);	// #O
							}
							break;
						case 11:
							possibleNextPoint[0] = std::make_pair(1, 0);	// ##
							possibleNextPoint[1] = std::make_pair(0, -1);	// #O
							break;
						case 12:
							possibleNextPoint[0] = std::make_pair(1, 0);	// OO
							possibleNextPoint[1] = std::make_pair(-1, 0);	// ##
							break;
						case 13:
							possibleNextPoint[0] = std::make_pair(1, 0);	// #O
							possibleNextPoint[1] = std::make_pair(0, 1);	// ##
							break;
						case 14:
							possibleNextPoint[0] = std::make_pair(0, 1);	// O#
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
					if(poly.points[poly.points.size() - 1].x + possibleNextPoint[0].first == poly.points[poly.points.size() - 2].x &&
						poly.points[poly.points.size() - 1].y + possibleNextPoint[0].second == poly.points[poly.points.size() - 2].y) // Checks which possible next point to use
					{
						poly.points.push_back(Point(poly.points[poly.points.size() - 1].x + possibleNextPoint[0].first, poly.points[poly.points.size() - 1].y + possibleNextPoint[0].second));
					}
					else
					{
						poly.points.push_back(Point(poly.points[poly.points.size() - 1].x + possibleNextPoint[1].first, poly.points[poly.points.size() - 1].y + possibleNextPoint[1].second));
					}
					
					if(poly.points[poly.points.size() - 1] == poly.points[0])
					{
						closed = true;
						poly.points.pop_back();
					}
				}
				for(unsigned int k = 0; k < poly.points.size(); k++)
				{
					if()
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
	height += 1.5 * noise.getHeightOctave((double)x / UPSCALE, (double)y / UPSCALE, 5, 0.2);

	return height;
}

std::array<bool, 4> IslandMaker::IslandData::getGridLandLocations(unsigned int xg, unsigned int yg)
{
	std::array<bool, 4> locations { false, false, false, false };

	if(xg != 0 && yg != boolMap.size())
	{
		locations[0] = boolMap[xg - 1][yg]; // Top left
	}
	if(xg != boolMap.size() && yg != boolMap.size())
	{
		locations[1] = boolMap[xg][yg]; // Top right
	}
	if(xg != boolMap.size() && yg != 0)
	{
		locations[2] = boolMap[xg][yg - 1]; // Bottom right
	}
	if(xg != 0 && yg != 0)
	{
		locations[3] = boolMap[xg - 1][yg - 1]; // Bottom left
	}

	return locations;
}
std::array<bool, 4> IslandMaker::IslandData::getLocationOpenEdges(unsigned int x, unsigned int y)
{
	std::array<bool, 4> edges { false, false, false, false };

	if(x != 0)
	{
		if(boolMap[x - 1][y] != boolMap[x][y]) // Left
		{
			edges[0] = true;
		}
	}
	else
	{
		edges[0] = true;
	}
	if(y != boolMap.size() - 1)
	{
		if(boolMap[x][y + 1] != boolMap[x][y]) // Top
		{
			edges[1] = true;
		}
	}
	else
	{
		edges[1] = true;
	}
	if(x != boolMap.size() - 1)
	{
		if(boolMap[x + 1][y] != boolMap[x][y]) // Right
		{
			edges[2] = true;
		}
	}
	else
	{
		edges[2] = true;
	}
	if(y != 0)
	{
		if(boolMap[x][y - 1] != boolMap[x][y]) // Bottom
		{
			edges[3] = true;
		}
	}
	else
	{
		edges[3] = true;
	}
}
unsigned int IslandMaker::IslandData::countTotalOpenEdges()
{
	unsigned int edgeCount = 0;

	for(unsigned int i = 0; i < UPSCALE * sizeFactor; i++)
	{
		for(unsigned int j = 0; j < UPSCALE * sizeFactor; j++)
		{
			std::array<bool, 4> edges = getLocationOpenEdges(i, j);

			edgeCount += edges[0] + edges[1] + edges[2] + edges[3];
		}
	}

	return edgeCount;
}