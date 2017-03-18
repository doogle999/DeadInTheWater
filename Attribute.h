#pragma once

#include <array>
#include <string>

class Attribute
{
	public:
		virtual ~Attribute() {};

		enum Ids
		{
			Translation,
			TimeoutTime,
			ReloadTime,
			HitPolygon,
			Orientation,
			META_ATTRIBUTE_COUNT
		};

		static const std::array<std::string, Ids::META_ATTRIBUTE_COUNT> ATTRIBUTE_NAMES;
};