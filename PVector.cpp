#include "PVector.h"

PVector::PVector() {}

PVector::~PVector() {}

PVector::PVector(double x, double y)
{
	this->x = x;
	this->y = y;
}

PVector PVector::operator*(const double scalar)
{
	PVector resultVector(this->x * scalar, this->y * scalar);

	return resultVector;
}

PVector PVector::operator+(const PVector& addedVector)
{
	PVector resultVector(this->x + addedVector.getX(), this->y + addedVector.getY());

	return resultVector;
}

PVector PVector::operator-(const PVector& subtractedVector)
{
	PVector resultVector(this->x - subtractedVector.getX(), this->y - subtractedVector.getY());

	return resultVector;
}

double PVector::magnitude() { return sqrt(x * x + y * y); }

void PVector::setXY(double x, double y) { this->x = x; this->y = y; }

double PVector::getX() const { return this->x; }
void PVector::setX(double x) { this->x = x; }

double PVector::getY() const { return this->y; }
void PVector::setY(double y) { this->y = y; }