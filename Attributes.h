#pragma once

#include "SFML/Graphics.hpp"

#include "Attribute.h"
#include "PVector.h"
#include "Polygon.h"

namespace A
{
	class Translation : public Attribute
	{
		public:
			Translation();

			PVector<double, 2> position;
			PVector<double, 2> velocity;
			PVector<double, 2> acceleration;
	};

	class TimeoutTime : public Attribute
	{
		public:
			TimeoutTime();

			double currentTimeoutTime;
	};

	class ReloadTime : public Attribute
	{
		public:
			ReloadTime();

			double reloadTime;
			double currentReloadTime;

			static const double DEFAULT_RELOAD_TIME;
	};

	class HitPolygon : public Attribute
	{
		public:
			HitPolygon();

			Polygon<double> hitPolygon;
	};

	class Orientation : public Attribute
	{
		public:
			Orientation();

			double theta;
			double omega;
			double alpha;
	};

	class IslandTriangles : public Attribute
	{
		public:
			IslandTriangles();

			sf::VertexArray triangles;
	};

	class ShipMovement : public Attribute
	{
		public:
			ShipMovement();

			double timeAfterStart;
			double startSpeed;
			double force;
			double maxForce;
			double rudder;
			double maxRudder;
			double dragL;
			double dragQ;
			double mass;

			double getSpeed(double t);

			double getTime(double v);

		private:
			double imaginaryLog(double x); // Only the imaginary component of the complex number
			double imaginaryLogInversePositive(double x); // Gives the positive half of the inverse of the imaginary log
			double imaginaryLogInverseNegative(double x); // Gives the negative half of the inverse of the imaginary log
	};
}
