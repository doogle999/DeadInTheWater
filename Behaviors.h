#pragma once

#include <map>
#include <string>

struct Behaviors
{
	enum Ids // It's important to note that all worlds have all behaviors, and that the enum values represent the indices of those behaviors in their behavior arrays
	{
		Id_IncrementPosition,
		Id_IncrementVelocity,
		Id_KillIfNotMoving,
		Id_KeyboardVelocity,
		Id_RenderCircle,

		Id_Collisions___StopOnCollision,
		Id_Selectables___SelectOnClick,
		Id_Camera2D___RenderCircle,

		META_BEHAVIOR_COUNT
	};

	static const std::map<std::string, Behaviors::Ids> behaviorRegistry;
};