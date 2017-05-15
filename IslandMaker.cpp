#include "IslandMaker.h"

IslandMaker::IslandMaker() {}

IslandMaker::~IslandMaker() {}

void IslandMaker::input()
{
	for(unsigned int r = 0; r < ei.size(); r++)
	{
		std::vector<std::vector<Polygon<double>>> polys = generateIslandsWithHeights(4, { -0.5, 0, 0.2, 0.6 } );

		sf::VertexArray& trianglesFinal = w->entities[ei[r]].AXS(IslandTriangles).triangles;

		unsigned int nextIndex = 0;

		for(unsigned int j = 0; j < polys.size(); j++)
		{
			for(unsigned int k = 0; k < polys[j].size(); k++)
			{
				polys[j][k].smooth();
				std::vector<Polygon<double>> triangles = polys[j][k].triangulate();

				trianglesFinal.resize(trianglesFinal.getVertexCount() + triangles.size() * 3);
				
				for(unsigned int i = 0; i < triangles.size(); i++)
				{
					trianglesFinal[trianglesFinal.getVertexCount() - 3 * i - 3].position = (triangles[i].points[0]).convert<float>().toVector2();
					trianglesFinal[trianglesFinal.getVertexCount() - 3 * i - 2].position = (triangles[i].points[1]).convert<float>().toVector2();
					trianglesFinal[trianglesFinal.getVertexCount() - 3 * i - 1].position = (triangles[i].points[2]).convert<float>().toVector2();

					sf::Color color;

					switch(j)
					{
						case 0:
							color = sf::Color(102, 204, 255);
							break;
						case 1:
							color = sf::Color(255, 255, 153);
							break;
						case 2:
							color = sf::Color(102, 255, 102);
							break;
						case 3:
							color = sf::Color(0, 153, 51);
							break;
					}
					trianglesFinal[trianglesFinal.getVertexCount() - 3 * i - 3].color = color;
					trianglesFinal[trianglesFinal.getVertexCount() - 3 * i - 2].color = color;
					trianglesFinal[trianglesFinal.getVertexCount() - 3 * i - 1].color = color;
				}
			}
		}
		w->scheduleToChangeFields(ei[r], Fields::Ids::Id_IslandMaker, false);
	}
}

std::vector<Polygon<double>> IslandMaker::generateIsland(IslandData islandData)
{
	std::vector<std::vector<bool>> unusedOpenEdge; // Locations of land that edge on water or the border
	unusedOpenEdge.resize(islandData.sizeFactor * UPSCALE);
	for(unsigned int i = 0; i < unusedOpenEdge.size(); i++)
	{
		unusedOpenEdge[i].resize(unusedOpenEdge.size());
	}

	for(unsigned int i = 0; i < UPSCALE * islandData.sizeFactor; i++)
	{
		for(unsigned int j = 0; j < UPSCALE * islandData.sizeFactor; j++)
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

	std::vector<Polygon<double>> polys; // Grid coordinaes between the squares, 1 larger in both directions than the boolmap

	for(unsigned int j = 0; j < UPSCALE * islandData.sizeFactor; j++) // Y position
	{
		for(unsigned int i = 0; i < UPSCALE * islandData.sizeFactor; i++) // X position
		{
			if(unusedOpenEdge[i][j])
			{
				Polygon<double> poly;

				std::array<bool, 4> isLakeOrIsland = islandData.getGridLandLocations(i, j); // If this is an internal lake, we should start 1 down because that's the actual edge
				if(isLakeOrIsland[0] + 2 * isLakeOrIsland[1] + 4 * isLakeOrIsland[2] + 8 * isLakeOrIsland[3] == 15)
				{
					poly.points.push_back(PVector<double, 2>({ (double)i, (double)j + 1.0 })); // Starting grid coordinates, bottom left of the square found
				}
				else
				{
					poly.points.push_back(PVector<double, 2>({ (double)i, (double)j })); // Starting grid coordinates, top left of the square found
				}

				std::array<bool, 4> temp = islandData.getLocationOpenEdges(poly.points.back().c[0], poly.points.front().c[1]);

				bool closed = false;
				while(!closed)
				{
					if(poly.points.size() % 2 == 0)
					{
						for(unsigned int k = 0; k < 4; k++) // Set the locations we used to used except if they can possibly be in two polygons
						{
							try
							{
								if(islandData.boolMap.at(poly.points[poly.points.size() - 2].c[0] - (k % 2)).at(poly.points[poly.points.size() - 2].c[1] - (k / 2)))
								{
									unusedOpenEdge.at(poly.points[poly.points.size() - 2].c[0] - (k % 2)).at(poly.points[poly.points.size() - 2].c[1] - (k / 2)) = false;
								}
							}
							catch(std::out_of_range) {}
						}
					}

					std::array<PVector<double, 2>, 2> possibleNextPoint;

					std::array<bool, 4> temp = islandData.getGridLandLocations(poly.points[poly.points.size() - 1].c[0], poly.points[poly.points.size() - 1].c[1]);
					unsigned char code = temp[0] + 2 * temp[1] + 4 * temp[2] + 8 * temp[3]; // The surroundings code number: top left determines 0 or 1, top right determines 0 or 2, bottom right determines 0 or 4, bottom left determiens 0 or 8, 16 possible cases
					
					if(poly.points.size() == 1)
					{
						poly.points.push_back(PVector<double, 2>(poly.points.back() + PVector<double, 2>({1.0, 0.0}))); // Step to the right, since we know below this square is nothing or water
					}
					else
					{
						switch(code)
						{
							case 1: 
								possibleNextPoint[0].c = {-1, 0};	// #O
								possibleNextPoint[1].c = {0, -1};	// OO
								break;
							case 2:
								possibleNextPoint[0].c = {1, 0};	// O#
								possibleNextPoint[1].c = {0, -1};	// OO
								break;
							case 3:
								possibleNextPoint[0].c = {1, 0};	// ##
								possibleNextPoint[1].c = {-1, 0};	// OO
								break;
							case 4:
								possibleNextPoint[0].c = {1, 0};	// OO
								possibleNextPoint[1].c = {0, 1};	// O#
								break;
							case 5:
								if(poly.points[poly.points.size() - 2].c[0] == poly.points[poly.points.size() - 1].c[0] - 1 || poly.points[poly.points.size() - 2].c[1] == poly.points[poly.points.size() - 1].c[1] - 1)
								{
									possibleNextPoint[0].c = {-1, 0};	// #O
									possibleNextPoint[1].c = {0, -1};	// O#
									unusedOpenEdge[poly.points.back().c[0]][poly.points.back().c[1]] = true;
								}
								else
								{
									possibleNextPoint[0].c = {1, 0};	// #O
									possibleNextPoint[1].c = {0, 1};	// O#
									unusedOpenEdge[poly.points.back().c[0] - 1][poly.points.back().c[1] - 1] = true;
								}
								break;
							case 6:
								possibleNextPoint[0].c = {0, -1};	// O#
								possibleNextPoint[1].c = {0, 1};	// O#
								break;
							case 7:
								possibleNextPoint[0].c = {-1, 0};	// ##
								possibleNextPoint[1].c = {0, 1};	// O#
								break;
							case 8:
								possibleNextPoint[0].c = {-1, 0};	// OO
								possibleNextPoint[1].c = {0, 1};	// #O
								break;
							case 9:
								possibleNextPoint[0].c = {0, 1};	// #O
								possibleNextPoint[1].c = {0, -1};	// #O
								break;
							case 10:
								if(poly.points[poly.points.size() - 2].c[0] == poly.points[poly.points.size() - 1].c[0] - 1 || poly.points[poly.points.size() - 2].c[1] == poly.points[poly.points.size() - 1].c[1] + 1)
								{
									possibleNextPoint[0].c = {-1, 0};	// O#
									possibleNextPoint[1].c = {0, 1};	// #O
									unusedOpenEdge[poly.points.back().c[0]][poly.points.back().c[1] - 1] = true;
								}
								else
								{
									possibleNextPoint[0].c = {1, 0};	// O#
									possibleNextPoint[1].c = {0, -1};	// #O
									unusedOpenEdge[poly.points.back().c[0]][poly.points.back().c[1] - 1] = true;
								}
								break;
							case 11:
								possibleNextPoint[0].c = {1, 0};	// ##
								possibleNextPoint[1].c = {0, 1};	// #O
								break;
							case 12:
								possibleNextPoint[0].c = {1, 0};	// OO
								possibleNextPoint[1].c = {-1, 0};	// ##
								break;
							case 13:
								possibleNextPoint[0].c = {1, 0};	// #O
								possibleNextPoint[1].c = {0, -1};	// ##
								break;
							case 14:
								possibleNextPoint[0].c = {0, -1};	// O#
								possibleNextPoint[1].c = {-1, 0};	// ##
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
						if(poly.points[poly.points.size() - 1] + possibleNextPoint[0] == poly.points[poly.points.size() - 2]) // Checks which possible next point to use
						{
							poly.points.push_back(poly.points[poly.points.size() - 1] + possibleNextPoint[1]);
						}
						else
						{
							poly.points.push_back(poly.points[poly.points.size() - 1] + possibleNextPoint[0]);
						}
					
						if(poly.points[poly.points.size() - 1] == poly.points[0]) // If we are on the same point as the beginning we are done
						{
							closed = true;
							poly.points.pop_back();
						}
					}
				}
				if(poly.points.size() > 6)
				{
					polys.push_back(poly);
				}
			}
		}
	}
	std::uniform_real_distribution<> dis(-0.3, 0.3);

	for(unsigned int i = 0; i < polys.size(); i++)
	{
		polys[i].smooth();
		for(unsigned int j = 0; j < polys[i].points.size(); j++)
		{
			polys[i].points[j] = polys[i].points[j] + PVector<double, 2>({ dis(Game::rng) , dis(Game::rng) });
		}
	}

	return polys;
}

std::vector<std::vector<Polygon<double>>> IslandMaker::generateIslandsWithHeights(unsigned int sizeFactor, std::vector<double> tiers)
{
	std::vector<std::vector<Polygon<double>>> returnVal;

	if(tiers.size() < 1)
	{
		return returnVal;
	}

	IslandData islandData(sizeFactor, 0);
	for(unsigned int i = 0; i < tiers.size(); i++)
	{
		islandData.threshold = tiers[i];
		islandData.generateIslandBoolMapNoLakes();
		returnVal.push_back(generateIsland(islandData));
	}
	return returnVal;
}

std::vector<Attribute::Ids> IslandMaker::getNecessaryProperties()
{
	return IslandMaker::necessaryProperties;
};

const std::vector<Attribute::Ids> IslandMaker::necessaryProperties = { Attribute::Ids::IslandTriangles };

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

	maxDistance = UPSCALE * sizeFactor / 2;
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
			if(getLocationIsBorder(i, j))
				boolMap[i][j] = 0;
			else
				boolMap[i][j] = getLocationHeight(i, j) > threshold;
		}
	}
}
void IslandMaker::IslandData::generateIslandBoolMapNoLakes()
{
	boolMap.resize(sizeFactor * UPSCALE);
	for(unsigned int i = 0; i < UPSCALE * sizeFactor; i++)
	{
		boolMap[i].resize(sizeFactor * UPSCALE);
		std::fill(boolMap[i].begin(), boolMap[i].end(), true);
	}

	floodFillGenerateBoolMapIterative(0, 0, false);
}
void IslandMaker::IslandData::floodFill(unsigned int x, unsigned int y, bool a)
{
	try
	{
		if(boolMap.at(x).at(y) != a) { return; }
		boolMap[x][y] = !boolMap[x][y];
		floodFill(x + 1, y, a);
		floodFill(x - 1, y, a);
		floodFill(x, y + 1, a);
		floodFill(x, y - 1, a);
	}
	catch(std::out_of_range) { return; }
}
void IslandMaker::IslandData::floodFillGenerateBoolMap(unsigned int x, unsigned int y, bool a)
{
	try
	{
		if((boolMap.at(x).at(y) == a || ((getLocationHeight(x, y) > threshold) != a && !getLocationIsBorder(x, y)))) { return; }
		boolMap[x][y] = a;
		floodFillGenerateBoolMap(x + 1, y, a);
		floodFillGenerateBoolMap(x - 1, y, a);
		floodFillGenerateBoolMap(x, y + 1, a);
		floodFillGenerateBoolMap(x, y - 1, a);
	}
	catch(std::out_of_range) { return; }
}
void IslandMaker::IslandData::floodFillIterative(unsigned int x, unsigned int y, bool a)
{
	struct pt { unsigned int x, y; };
	std::stack<pt> stack;
	stack.push({ x, y });

	while(!stack.empty())
	{
		pt top = stack.top();
		stack.pop();
		try
		{
			if(boolMap.at(top.x).at(top. y) == a)
			{
				boolMap[top.x][top.y] = !boolMap[top.x][top.y];
				stack.push({ top.x + 1, top.y });
				stack.push({ top.x - 1, top.y });
				stack.push({ top.x, top.y + 1 });
				stack.push({ top.x, top.y - 1 });
			}
		}
		catch(std::out_of_range) {}
	}
}
void IslandMaker::IslandData::floodFillGenerateBoolMapIterative(unsigned int x, unsigned int y, bool a)
{
	struct pt { unsigned int x, y; };
	std::stack<pt> stack;
	stack.push({ x, y });

	while(!stack.empty())
	{
		pt top = stack.top();
		stack.pop();
		try
		{
			if(boolMap.at(top.x).at(top.y) != a && (((getLocationHeight(top.x, top.y) > threshold) == a) || getLocationIsBorder(top.x, top.y)))
			{
				boolMap[top.x][top.y] = a;
				stack.push({ top.x + 1, top.y });
				stack.push({ top.x - 1, top.y });
				stack.push({ top.x, top.y + 1 });
				stack.push({ top.x, top.y - 1 });
			}
		}
		catch(std::out_of_range) {}
	}
}


double IslandMaker::IslandData::getLocationHeight(unsigned int x, unsigned int y)
{
	double distance = sqrt((double)((x - UPSCALE * sizeFactor / 2) * (x - UPSCALE * sizeFactor / 2)) + (double)((y - UPSCALE * sizeFactor / 2) * (y - UPSCALE * sizeFactor / 2))); // Distance from center
	double height = -2 * distance / maxDistance + 1.0;
	height += 1.5 * noise.getHeightOctave((double)x / UPSCALE, (double)y / UPSCALE, 5, 0.2);

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
	return x == 0 || y == 0 || x == UPSCALE * sizeFactor - 1 || y == UPSCALE * sizeFactor - 1;
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