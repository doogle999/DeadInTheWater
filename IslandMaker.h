#pragma once

#include <vector>
#include <array>
#include <exception>
#include <algorithm>
#include <numeric>
#include <math.h>

#include "Properties.h"
#include "Game.h"
#include "Entity.h"
#include "Field.h"
#include "PVector.h"
#include "Polygon.h"

class Entity;
class RenderBoat;
class RenderProjectile;

class IslandMaker : public Field
{
	public:
		IslandMaker();

		~IslandMaker();

		virtual std::vector<P::Ids> getNecessaryProperties();

		// Generates the polygon (or polygons, if there are surrounding islets) that describe an island, the size of the island is sizeFactor times the UPSCALE constant	
		std::vector<Polygon<unsigned int>> generateIsland(unsigned int sizeFactor, double threshold);

	private:
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

		class IslandData
		{
			public:
				IslandData(unsigned int sizeFactor, double threshold);

				~IslandData();

				double getLocationHeight(unsigned int x, unsigned int y); // Gets the height of an location

				std::array<bool, 4> getGridLandLocations(unsigned int xg, unsigned int yg); // Gets whether the locations around a grid intersection are land or water, top left going clockwise is the order, the grid's origin is the top left
				bool getLocationIsBorder(unsigned int x, unsigned int y); // Is this location one the edge of the map
				std::array<bool, 4> getLocationOpenEdges(unsigned int x, unsigned int y); // Gets the open edges of a location, left going clockwise is the order, the locations' origin is the top left
				unsigned char countLocationOpenEdges(unsigned int x, unsigned int y); // Counts the number of open edges for a location
				unsigned int countTotalOpenEdges(); // Counts the total number of open edges for all locations

				std::vector<std::vector<bool>> boolMap; // A map of the island and the water surrounding it that says if there is land or water at a location
			private:
				void generateIslandBoolMap(); // Generates a map of the island and the water surrounding it that says if there is land or water at a location, use this before using the edge functions

				Noise noise; // The noise pattern for this island
				
				unsigned int sizeFactor; // This times UPSCALE is the size
				double threshold; // Above this value is land
				double maxDistance; // The farthest distance from the center of the island
		};
};