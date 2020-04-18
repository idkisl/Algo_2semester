#pragma once

struct Point
{
private:
	bool _isEqual(double a, double b) const
	{
		return a - b <= 1e-9 && b - a <= 1e-9;
	}
public:
	double x;
	double y;
	explicit Point(double x = 0, double y = 0): x(x), y(y){}
	bool operator==(const Point& right) const { return (_isEqual(x, right.x) && _isEqual(y, right.y)) ? true : false; }
	bool operator!=(const Point& right) const { return (_isEqual(x, right.x) && _isEqual(y, right.y)) ? false : true; }
};