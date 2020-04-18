#pragma once
#include "Shape.h"
#include <utility>
class Ellipse : public Shape
{
	double _findAxialTilt() const;
protected:
	std::pair<Point, Point> focus;
	Point centre;
	double big, small; // большая и малая полуоси
public:
	std::pair<Point, Point> focuses() {return focus;} // его фокусы
	std::pair<Line, Line> directrices(); // пару его директрис
	double eccentricity(); // -его эксцентриситет
	Point center() {return centre;} // его центр
	Ellipse(const Point& a, const Point& b, double dist); // два фокуса и сумма расстояний от эллипса до них
	double perimeter() const;
	double area() const;
	bool operator==(const Shape& another) const;
	bool operator!=(const Shape& another) const;
	bool isCongruentTo(const Shape& another) const;
	bool isSimilarTo(const Shape& another) const;
	bool containsPoint(const Point& point) const; // находится ли точка внутри фигуры. 
	void rotate(const Point& center, double angle);
	void reflex(const Point& center);
	void scale(Point center, double coefficient); // гомотетию с коэффициентом coefficient и центром center.
	void reflex(const Line& axis); // симметрию относительно прямой
};