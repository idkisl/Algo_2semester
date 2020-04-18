#pragma once
#include "Shape.h"
//#include <utility>
class Ellips : public Shape
{
public:
	std::pair<Point, Point> focuses() = 0; // его фокусы
	std::pair<Line, Line> directrices() = 0; // пару его директрис
	double eccentricity() = 0; // -его эксцентриситет
	Point center() = 0; // его центр
	Ellips(const Point& a, const Point& b, double dist) {}; // два фокуса и сумма расстояний от эллипса до них
};