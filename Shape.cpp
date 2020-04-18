#include "Shape.h"

void Shape::_reversePoint(const Point& center, Point& point) const
{
	double delta_x = center.x - point.x;
	double delta_y = center.y - point.y;
	point.x = center.x + delta_x;
	point.y = center.y + delta_y;
}

void Shape::_rotatePoint(const Point& center, Point& point, double angle) const
{
	// перешли в СО, связанную с center
	point.x -= center.x;
	point.y -= center.y;
	Point new_point;
	new_point.x = point.x * cos(angle) - point.y * sin(angle);
	new_point.y = point.x * sin(angle) + point.y * cos(angle);
	new_point.x += center.x;
	new_point.y += center.y;
	point = new_point;
}

void Shape::_scalePoint(const Point& center, Point& point, double coefficient) const
{
	point.x -= center.x;
	point.y -= center.y;
	point.x *= coefficient;
	point.y *= coefficient;
	point.x += center.x;
	point.y += center.y;
}

void Shape::_reflexPointFromLine(const Line& axis, Point& point) const
{
	std::pair<double, double> line = axis.returnLine();
	double k1 = -1 / line.first;
	double b1 = point.y - k1 * point.x;

	Point point_on_line;
	point_on_line.x = (line.second - b1) / (k1 - line.first);
	point_on_line.y = k1 * point_on_line.x + b1;
	Point new_point = point_on_line;
	new_point.x -= point.x;
	new_point.y -= point.y;
	new_point.x *= 2;
	new_point.y *= 2;
	new_point.x += point.x;
	new_point.y += point.y;
	point = new_point;
}