#pragma once
#include "Polygon.h"
#include "Circle.h"

class Triangle : public Polygon
{
	Point _centerOfCircumscribedCircle() const;
public:
	Triangle(std::vector<Point> vec) : Polygon(vec) {}
	Triangle(const Point& a, const Point& b, const Point& c) : Polygon(a,b,c) {}
	Circle circumscribedCircle() const; // ��������� o���������
	Circle inscribedCircle() const;
	Point centroid() const; // ��� ����� ����
	Point orthocenter() const; // ��� ���������
	Line EulerLine() const; // ��� ������ ������
	Circle ninePointsCircle() const; //��� ���������� ������
};