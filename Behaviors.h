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

		Id_Collisions_StopOnCollision,
		Id_Selectables_SelectOnClick,
		Id_Camera2D_RenderCircle
	};

	static const std::map<std::string, Behaviors::Ids> behaviorRegistry;
};