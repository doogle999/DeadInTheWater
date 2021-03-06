#include "Fields.h"

#define ADD_NAME(NAME) {#NAME, Fields::Ids::Id_ ## NAME}

const std::map<std::string, Fields::Ids> Fields::fieldRegistry
{
	ADD_NAME(SFMLInputHandler),
	ADD_NAME(Player),
	ADD_NAME(ShipController),
	ADD_NAME(TranslationIncrementer),
	ADD_NAME(Camera2D),
	ADD_NAME(RenderBoat),
	ADD_NAME(SpawnProjectile),
	ADD_NAME(RenderProjectile),
	ADD_NAME(Timeout),
	ADD_NAME(OrientationIncrementer),
	ADD_NAME(IslandMaker),
	ADD_NAME(RenderIsland)
};

#undef ADD_NAME