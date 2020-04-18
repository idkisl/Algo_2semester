#pragma once
#include "Polygon.h"

class Rectangle : public Polygon
{
protected:
	static const int SHIFT = 100;
public:
	explicit Rectangle(const Point& a, const Point& , double k); // �� ���� ������������ Point � tg ���� ������� ���������
	explicit Rectangle(std::vector<Point> vertices) : Polygon(vertices) {}
	Point center() const;
	std::pair<Line, Line> diagonals() const;
	bool isConvex() const { return true; }
};