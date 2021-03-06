#pragma once

#include <vector>

#include "Entity.h"
#include "Field.h"
#include "PVector.h"
#include "SFMLInputHandler.h"

class Entity;

class Camera2D : public Field
{
	public:
		Camera2D();

		~Camera2D();
		
		virtual void update();

		void cameraControls(std::array<SFMLInputHandler::Func, 6> f);

		PVector<double, 2> screenPosToGamePos(PVector<double, 2> sp);
		PVector<double, 2> gamePosToScreenPos(PVector<double, 2> sp);

		void setViewportPos(PVector<double, 2> p);
		void setViewportVel(PVector<double, 2> v);

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