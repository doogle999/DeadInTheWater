#include "Properties.h"

#define ADD_SIZE(NAME) {P::Ids:: ## NAME, sizeof(P::TYPE_ ## NAME)}
#define ADD_NAME(NAME) {#NAME, P::Ids:: ## NAME}

const std::map<P::Ids, size_t> P::Sizes
{
	ADD_SIZE(xPosition),
	ADD_SIZE(yPosition),
	ADD_SIZE(xVelocity),
	ADD_SIZE(yVelocity),
	ADD_SIZE(radius)
};

const std::map<std::string, P::Ids> P::Names
{
	ADD_NAME(xPosition),
	ADD_NAME(yPosition),
	ADD_NAME(xVelocity),
	ADD_NAME(yVelocity),
	ADD_NAME(radius)
};

#undef ADD_SIZE
#undef ADD_NAME