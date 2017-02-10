#include "IslandMaker.h"

IslandMaker::IslandMaker() {}

IslandMaker::~IslandMaker() {}

std::vector<P::Ids> IslandMaker::getNecessaryProperties()
{
	return IslandMaker::necessaryProperties;
};

const std::vector<P::Ids> IslandMaker::necessaryProperties = {};

IslandMaker::Noise::Noise(unsigned int period)
{
	std::iota(permutations.begin(), permutations.end(), 0);
	std::shuffle(permutations.begin(), permutations.end(), Game::rng);

	this->period = period;
}

IslandMaker::Noise::~Noise() {}

std::vector<std::vector<bool>> IslandMaker::generateIslandHeightMap(unsigned int sizeFactor)
{
	Noise noise(sizeFactor);

	for(unsigned int i = 0; i < 16 * sizeFactor; i++)
	{
		for(unsigned int j = 0; j < 16 * sizeFactor; j++)
		{
			
		}
	}
}

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

