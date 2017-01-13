#pragma once

#include "SFML\Window\Keyboard.hpp"

#include <vector>

#include "Properties.h"
#include "Entity.h"
#include "Field.h"

class Entity;

class Camera2D : public Field
{
	public:
		Camera2D();

		~Camera2D();

		virtual void input();
		
		virtual void update();

		virtual void render();

		virtual std::vector<P::Ids> getNecessaryProperties();

	private:
		static const std::vector<P::Ids> necessaryProperties;

		double viewportX; // X position of the left of the viewport, measured from the left of the screen rightward
		double viewportY; // Y position of the top of the viewport, measured from the top of the screen downard
		double viewportS; // Scaling of the viewport based on the window, bigger numbers means bigger viewport

		double viewportXVelocity; // Independent of scale
		double viewportYVelocity;
		double viewportSFactor;
};