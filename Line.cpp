#include "Line.h"
bool Line::_isEqual(double a, double b) const
{
	return a - b <= 1e-9 && b - a <= 1e-9;
}

bool Line::isParallel(const Line& another) const
{
	if (_isEqual(a.x, b.x) || _isEqual(another.a.x, another.b.x))
	{
		if (_isEqual(a.y, another.a.y) && _isEqual(b.y, another.b.y))
			return true;
		return false;
	}
	if (_isEqual((a.y - b.y) / (a.x - b.x), (another.a.y - another.b.y) / (another.a.x - another.b.x)))
		return true;
	return false;
}
bool Line::operator==(const Line& another)const
{
	double k1 = (a.y - b.y) / (a.x - b.x);
	double k2 = (another.a.y - another.b.y) / (another.a.x - another.b.x);
	if (!_isEqual(k1, k2))
		return false;
	if (_isEqual((a.y - a.x * k1), (another.a.y - another.a.x * k2)))
		return true;
	return false;
}

std::pair<double, double> Line::returnLine() const
{
	double k = (a.y - b.y) / (a.x - b.x);
	double c = b.y - k * b.x;
	return std::make_pair(k, c);
}