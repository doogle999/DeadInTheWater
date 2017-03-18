#pragma once

#include <map>
#include <string>

struct Fields
{
	enum Ids // It's important to note that all worlds have all fields, and that the enum values represent the indices of those fields in their field arrays
	{
		Id_SFMLInputHandler,
		Id_Player,
		Id_ShipController,
		Id_TranslationIncrementer,
		Id_Camera2D,
		Id_RenderBoat,
		Id_SpawnProjectile,
		Id_RenderProjectile,
		Id_Timeout,
		Id_OrientationIncrementer,
		META_FIELD_COUNT
	};

	static const std::map<std::string, Fields::Ids> fieldRegistry;
};