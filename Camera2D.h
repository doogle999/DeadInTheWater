#pragma once

#include "SFML\Window\Keyboard.hpp"

#include <vector>

#include "Entity.h"
#include "Field.h"
#include "PVector.h"

class Entity;

class Camera2D : public Field
{
	public:
		Camera2D();

		~Camera2D();

		virtual void input();
		
		virtual void update();

		PVector<double, 2> screenPosToGamePos(PVector<double, 2> sp);
		PVector<double, 2> gamePosToScreenPos(PVector<double, 2> sp);

		PVector<double, 2> getViewportPos();
		PVector<double, 2> getViewportVel();

		double getViewportS();
		double getViewportSMult();

		virtual std::vector<Attribute::Ids> getNecessaryProperties();

	private:
		PVector<double, 2> viewportPos; // X, Y, origin in top left, 
		PVector<double, 2> viewportVel; // X, Y, independent of scale

		double viewportS; // Scale: bigger numbers means bigger viewport
		double viewportSMult; // Scale multiplier
};