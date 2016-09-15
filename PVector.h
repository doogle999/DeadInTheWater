#pragma once

#include <Math.h>

class PVector
{
	private:
		double x;
		double y;

	public:
		PVector();

		PVector(double x, double y);

		PVector operator*(const double scalar);

		PVector operator+(const PVector& addedVector);

		PVector operator-(const PVector& subtractedVector);

		double magnitude();

		void setXY(double x, double y);

		double getX() const;
		void setX(double x);

		double getY() const;
		void setY(double y);

		~PVector();
};