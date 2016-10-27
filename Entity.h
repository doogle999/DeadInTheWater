#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Properties.h"
#include "Behavior.h"

class Behavior;

class Entity
{
	public:
		Entity(std::vector<P> p);

		bool compatible(Behavior* b);				// Checks if this object has all the properties necessary for a behavior

		bool addInputer(Behavior* b);				// Adds an inputer if compatible and returns true, otherwise returns false
		bool addUpdater(Behavior* b);				// Adds an updater if compatible and returns true, otherwise returns false
		bool addRenderer(Behavior* b);				// Adds a renderer if compatible and returns true, otherwise returns false

		void input();								// Runs all the inputers
		void update();								// Runs all the updaters
		void render();								// Runs all the renderers

		double getPDouble(int i);
		void setPDouble(int i, double v);

		int getPInt(int i);
		void setPInt(int i, int v);

		~Entity();

	private:
		std::vector<P> ps;							// A list of all the properties that this object has

		std::unordered_map<int, double> pDouble;	// The double properties of this object
		std::unordered_map<int, int> pInt;			// The int properties of this object

		std::vector<Behavior*> inputers;			// Pointers to the input behaviors this object employs
		std::vector<Behavior*> updaters;			// Pointers to the update behaviors this object employs 
		std::vector<Behavior*> renderers;			// Pointers to the render behaviors this object employs
};
