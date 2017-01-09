#include "Behaviors.h"

#define ADD_NAME(NAME) {#NAME, Behaviors::Ids::Id_ ## NAME}

const std::map<std::string, Behaviors::Ids> Behaviors::behaviorRegistry
{
	ADD_NAME(IncrementPosition),
	ADD_NAME(IncrementVelocity),
	ADD_NAME(KillIfNotMoving),
	ADD_NAME(KeyboardVelocity),
	ADD_NAME(RenderCircle),

	ADD_NAME(Collisions___StopOnCollision),
	ADD_NAME(Selectables___SelectOnClick),
	ADD_NAME(Camera2D___RenderCircle)
};

#undef ADD_NAME