#include "Fields.h"

#define ADD_NAME(NAME) {#NAME, Fields::Ids::Id_ ## NAME}

const std::map<std::string, Fields::Ids> Fields::fieldRegistry
{
	ADD_NAME(TranslationIncrementer),
	ADD_NAME(Camera2D),
	ADD_NAME(RenderBoat),
	ADD_NAME(SpawnProjectile),
	ADD_NAME(RenderProjectile),
	ADD_NAME(Timeout)
};

#undef ADD_NAME