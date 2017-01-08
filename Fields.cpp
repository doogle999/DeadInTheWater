#include "Fields.h"

#define ADD_NAME(NAME) {#NAME, Fields::Ids::Id_ ## NAME}

const std::map<std::string, Fields::Ids> Fields::fieldRegistry
{
	ADD_NAME(Selectables),
	ADD_NAME(Collisions),
	ADD_NAME(Gravity),
	ADD_NAME(Selectables)
};

#undef ADD_NAME