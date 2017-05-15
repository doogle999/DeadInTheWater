#include "Attribute.h"

const std::array<std::string, Attribute::Ids::META_ATTRIBUTE_COUNT> Attribute::ATTRIBUTE_NAMES = // Do this in the same order as the enum, for obvious reasons...
{
	"Translation",
	"TimeoutTime",
	"ReloadTime",
	"HitPolygon",
	"Orientation",
	"IslandTriangles",
	"ShipMovement"
};