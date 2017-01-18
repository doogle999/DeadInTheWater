#include "Properties.h"

#define ADD_SIZE(NAME) {P::Ids:: ## NAME, sizeof(P::TYPE_ ## NAME)}
#define ADD_NAME(NAME) {#NAME, P::Ids:: ## NAME}

const std::map<P::Ids, size_t> P::Sizes
{
	ADD_SIZE(xPosition),
	ADD_SIZE(yPosition),
	ADD_SIZE(xVelocity),
	ADD_SIZE(yVelocity),
	ADD_SIZE(xAcceleration),
	ADD_SIZE(yAcceleration),
	ADD_SIZE(selected),
	ADD_SIZE(radius),
	ADD_SIZE(mass),
	ADD_SIZE(reloadTime),
	ADD_SIZE(color),
	ADD_SIZE(renderRadius),
	ADD_SIZE(timeoutTime)
};

const std::map<std::string, P::Ids> P::Names
{
	ADD_NAME(xPosition),
	ADD_NAME(yPosition),
	ADD_NAME(xVelocity),
	ADD_NAME(yVelocity),
	ADD_NAME(xAcceleration),
	ADD_NAME(yAcceleration),
	ADD_NAME(selected),
	ADD_NAME(radius),
	ADD_NAME(mass),
	ADD_NAME(reloadTime),
	ADD_NAME(color),
	ADD_NAME(renderRadius),
	ADD_NAME(timeoutTime)
};

#undef ADD_SIZE
#undef ADD_NAME