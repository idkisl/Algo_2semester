#include "Ellipse.h"

double Ellipse::_findAxialTilt() const
{
	if (focus.second.x == focus.first.x)
		return M_PI / 2;
	double tg = (focus.second.y - focus.first.y) / (focus.second.x - focus.first.x);
	return atan(tg);
}

Ellipse::Ellipse(const Point& a, const Point& b, double dist)
{
	focus.first = a.x > b.x ? b : a;
	focus.second = a.x > b.x ? a : b;
	centre.x = (a.x + b.x) / 2;
	centre.y = (a.y + b.y) / 2;
	big = dist / 2;
	small = sqrt(dist * dist / 4 - ((focus.first.x - centre.x) * (focus.first.x - centre.x) + (focus.first.y - centre.y) * (focus.first.y - centre.y)));
}

double Ellipse::eccentricity()
{
	return (sqrt(big * big - small * small)) / big;
}

std::pair<Line, Line> Ellipse::directrices()
{
	double titl_angle = _findAxialTilt();
	double l = big * big / small;
	Line d1(Point(l * cos(titl_angle) + centre.x, centre.y), Point(l * cos(titl_angle) * 2 + centre.x, centre.y ));
	Line d2(Point(-l * cos(titl_angle) + centre.x, centre.y), Point(-l * cos(titl_angle) * 2 + centre.x, centre.y));
	std::pair<Line, Line> dir (d1, d2);
	return dir;
}

double Ellipse::perimeter() const
{
	return M_PI * (3 * (big + small) - sqrt((3 * big + small) * (big + 3 * small)));
}

double Ellipse::area() const
{
	return M_PI * big * small;
}

bool Ellipse::operator==(const Shape& another) const
{
	const Ellipse* other = dynamic_cast<const Ellipse*> (&another);
	if (other == nullptr)
		return false;
	Line f1f2_1(focus.first, focus.second);
	Line f1f2_2(other->focus.first, other->focus.second);
	if (!f1f2_1.isParallel(f1f2_2))
		return false;
	if (small == other->small && big == other->big)
		return true;
	return false;
}

bool Ellipse::operator!=(const Shape& another) const
{
	return !(*this == another);
}

bool Ellipse::isCongruentTo(const Shape& another) const
{
	const Ellipse* other = dynamic_cast<const Ellipse*> (&another);
	if (other == nullptr)
		return false;

	if (small == other->small && big == other->big)
		return true;
	return false;
}

bool Ellipse::isSimilarTo(const Shape& another) const
{
	const Ellipse* other = dynamic_cast<const Ellipse*> (&another);
	if (other == nullptr)
		return false;
	
	double k1 = big / small;
	double k2 = other->big / other->small;
	if (k1 == k2)
		return true;
	return false;
}

bool Ellipse::containsPoint(const Point& point) const
{
	double distance = 2 * big;
	double dist_to_f1 = sqrt((point.x - focus.first.x) * (point.x - focus.first.x) +
		(point.y - focus.first.y) * (point.y - focus.first.y));
	double dist_to_f2 = sqrt((point.x - focus.second.x) * (point.x - focus.second.x) +
		(point.y - focus.second.y) * (point.y - focus.second.y));
	if ((dist_to_f1 + dist_to_f2) <= distance)
		return true;
	return false;
}

void Ellipse::rotate(const Point& center, double angle)
{
	angle *= M_PI / 180;
	_rotatePoint(center, focus.first, angle);
	_rotatePoint(center, focus.second, angle);
	_rotatePoint(center, centre, angle);
}

void Ellipse::reflex(const Point& center)
{
	_reversePoint(center, focus.first);
	_reversePoint(center, focus.second);
	_reversePoint(center, centre);
}

void Ellipse::scale(Point center, double coefficient)
{
	_scalePoint(center, focus.first, coefficient);
	_scalePoint(center, focus.second, coefficient);
	_scalePoint(center, centre, coefficient);

	big *= coefficient;
	small *= coefficient;
}

void Ellipse::reflex(const Line& axis)
{
	_reflexPointFromLine(axis, focus.first);
	_reflexPointFromLine(axis, focus.second);
	_reflexPointFromLine(axis, centre);
}