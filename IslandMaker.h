#pragma once

#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <numeric>
#include <math.h>

#include "Properties.h"
#include "Game.h"
#include "Entity.h"
#include "Field.h"
#include "Point.h"

class Entity;
class RenderBoat;
class RenderProjectile;

class IslandMaker : public Field
{
	public:
		IslandMaker();

		~IslandMaker();

		virtual std::vector<P::Ids> getNecessaryProperties();

	//private:
		static const std::vector<P::Ids> necessaryProperties;

		static const unsigned int UPSCALE = 16;

		class Noise // Perlin Noise, with octaves
		{
			public:
				Noise(unsigned int period);

				~Noise();

				double getHeight(double x, double y) const;

				double getHeightOctave(double x, double y, unsigned int octaves, double persistence);

			private:
				int IslandMaker::Noise::increment(int t) const;

				static double lerp(double a, double b, double x);

				static double grad(int hash, double x, double y);

				static double fade(double t);

				unsigned int period;

				static const unsigned int SIZE = 256;

				std::array<unsigned char, SIZE> permutations;
		};

		//std::vector<> generateIsland(unsigned int sizeFactor); // Generates the polygon (or polygons, if there are surrounding islets) that describe an island, the size of the island is sizeFactor times the UPSCALE constant

		std::vector<std::vector<bool>> generateIslandBoolMap(unsigned int sizeFactor, double threshold); // Generates a map of the island and the water surrounding it that says if there is land or water at a point, threshold is a value between -1 and 1 that specifies above what value is land
};