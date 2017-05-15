#include "Attributes.h"

using namespace A;

Translation::Translation() : position({ 0, 0 }), velocity({ 0, 0 }), acceleration({ 0, 0 }) {};

TimeoutTime::TimeoutTime() : currentTimeoutTime(0) {};

ReloadTime::ReloadTime() : reloadTime(DEFAULT_RELOAD_TIME), currentReloadTime(0) {};
const double ReloadTime::DEFAULT_RELOAD_TIME = 5;

HitPolygon::HitPolygon() : hitPolygon({ }) {};

Orientation::Orientation() : theta(0), omega(0), alpha(0) {};

IslandTriangles::IslandTriangles() : triangles(sf::Triangles) {};

ShipMovement::ShipMovement() : force(0), maxForce(1), dragL(1), dragQ(1), mass(1) {};
double ShipMovement::getSpeed(double t)
{

}
double ShipMovement::imaginaryLog(double x) { return log(1 - x * x + x * x * x * x) / 4.0 - log(1 + x * x + x * x * x * x) / 2.0; }
double ShipMovement::imaginaryLogInverseNegative(double x) { return -(1 + exp(2 * x)) / (exp(2 * x) - 1); }
double ShipMovement::imaginaryLogInversePositive(double x) { return (1 - exp(2 * x)) / (exp(2 * x) + 1); }