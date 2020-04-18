#pragma once
#include "Polygon.h"
#include "Circle.h"

class Triangle : public Polygon
{
	Point _centerOfCircumscribedCircle() const;
public:
	Triangle(std::vector<Point> vec) : Polygon(vec) {}
	Triangle(const Point& a, const Point& b, const Point& c) : Polygon(a,b,c) {}
	Circle circumscribedCircle() const; // описанна€ oкружность
	Circle inscribedCircle() const;
	Point centroid() const; // его центр масс
	Point orthocenter() const; // его ортоцентр
	Line EulerLine() const; // его пр€мую Ёйлера
	Circle ninePointsCircle() const; //его окружность Ёйлера
};