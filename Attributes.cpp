#include "Attributes.h"

using namespace A;

Translation::Translation() : position({ 0, 0 }), velocity({ 0, 0 }), acceleration({ 0, 0 }) {};

TimeoutTime::TimeoutTime() : currentTimeoutTime(0) {};

ReloadTime::ReloadTime() : reloadTime(DEFAULT_RELOAD_TIME), currentReloadTime(0) {};
const double ReloadTime::DEFAULT_RELOAD_TIME = 5;