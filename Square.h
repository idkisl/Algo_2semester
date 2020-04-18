#pragma once
#include "Rectangle.h"
#include "Circle.h"

class Square : public Rectangle
{
public:
	Square(const Point& a, const Point& c) : Rectangle(a, c, 1) {}
	Circle circumscribedCircle() const; // описанная окружность
	Circle inscribedCircle() const;
};
