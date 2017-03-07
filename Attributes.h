#pragma once

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
}
