#pragma once
#include "Ellipse.h"

class Circle : public Ellipse
{
public:
	Circle(const Point& center, double r);
	double radius() { return big; }
};