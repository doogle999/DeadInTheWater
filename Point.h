#pragma once

struct Point
{
	public:
		Point() {};
		Point(double x, double y) : x(x), y(y) {};
		Point(const Point& p) : x(p.x), y(p.y) {};

		Point& operator=(const Point& p) 
		{
			x = p.x;
			y = p.y;

			return *this;
		};

		bool operator==(const Point& p)
		{
			return (x == p.x && y == p.y);
		};

		~Point() {};

		double x;
		double y;
};