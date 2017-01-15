#pragma once

#include <map>
#include <string>

struct Fields
{
	enum Ids // It's important to note that all worlds have all fields, and that the enum values represent the indices of those fields in their field arrays
	{
		Id_Selectables,
		Id_Collisions,
		Id_Gravity,
		Id_Camera2D,
		Id_RenderBoat,
		META_FIELD_COUNT
	};

	static const std::map<std::string, Fields::Ids> fieldRegistry;
};