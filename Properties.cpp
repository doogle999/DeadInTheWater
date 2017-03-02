#include "Properties.h"

#define ADD_SIZE(NAME) {P::Ids:: ## NAME, sizeof(P::TYPE_ ## NAME)}
#define ADD_NAME(NAME) {#NAME, P::Ids:: ## NAME}

const std::map<P::Ids, size_t> P::Sizes
{
	ADD_SIZE(position),
	ADD_SIZE(velocity),
	ADD_SIZE(acceleration),
	ADD_SIZE(orientation),
	ADD_SIZE(orientationVelocity),
	ADD_SIZE(reloadTime),
	ADD_SIZE(timeoutTime),
	ADD_SIZE(hitPolygon)
};

const std::map<std::string, P::Ids> P::Names
{
	ADD_NAME(position),
	ADD_NAME(velocity),
	ADD_NAME(acceleration),
	ADD_NAME(orientation),
	ADD_NAME(orientationVelocity),
	ADD_NAME(reloadTime),
	ADD_NAME(timeoutTime),
	ADD_NAME(hitPolygon)
};

#undef ADD_SIZE
#undef ADD_NAME