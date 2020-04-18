#pragma once
#include "Shape.h"
#include <utility>
class Ellipse : public Shape
{
	double _findAxialTilt() const;
protected:
	std::pair<Point, Point> focus;
	Point centre;
	double big, small; // ������� � ����� �������
public:
	std::pair<Point, Point> focuses() {return focus;} // ��� ������
	std::pair<Line, Line> directrices(); // ���� ��� ���������
	double eccentricity(); // -��� ��������������
	Point center() {return centre;} // ��� �����
	Ellipse(const Point& a, const Point& b, double dist); // ��� ������ � ����� ���������� �� ������� �� ���
	double perimeter() const;
	double area() const;
	bool operator==(const Shape& another) const;
	bool operator!=(const Shape& another) const;
	bool isCongruentTo(const Shape& another) const;
	bool isSimilarTo(const Shape& another) const;
	bool containsPoint(const Point& point) const; // ��������� �� ����� ������ ������. 
	void rotate(const Point& center, double angle);
	void reflex(const Point& center);
	void scale(Point center, double coefficient); // ��������� � ������������� coefficient � ������� center.
	void reflex(const Line& axis); // ��������� ������������ ������
};