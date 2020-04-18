#pragma once
#include "Shape.h"
//#include <utility>
class Ellips : public Shape
{
public:
	std::pair<Point, Point> focuses() = 0; // ��� ������
	std::pair<Line, Line> directrices() = 0; // ���� ��� ���������
	double eccentricity() = 0; // -��� ��������������
	Point center() = 0; // ��� �����
	Ellips(const Point& a, const Point& b, double dist) {}; // ��� ������ � ����� ���������� �� ������� �� ���
};