#pragma once
#include "Point.h"
#include <utility>

class Line
{
	bool _isEqual(double a, double b) const;
	static const int SHIFT = 100;
	Point a;
	Point b;
public:
	explicit Line(const Point& a, const Point& b): a(a), b(b) {}
	explicit Line(double k, double shift): a(0, shift), b(SHIFT, (double(SHIFT) / k) + shift){} // где k - коэффициент наклона, а shift - смещение по оси y
	explicit Line(const Point& a, double k) : a(a), b(a.x + SHIFT, k * SHIFT + a.y) {}
	//returns : first - is k, second is b in y = kx + b
	std::pair<double, double> returnLine() const;
	bool isParallel(const Line& another) const;
	bool operator==(const Line& right)const;
	bool operator!=(const Line& right)const
	{
		return !(*this == right);
	}
};