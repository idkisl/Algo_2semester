#pragma once
#include "Point.h"
#include "Line.h"
#include <iostream>
#define M_PI 3.14159265358979323846
#include <cmath>

class Shape
{
protected:
	void _reversePoint(const Point& center, Point& point) const;
	void _rotatePoint(const Point& center, Point& point, double angle) const;
	void _scalePoint (const Point& center, Point& point, double coefficient) const;
	void _reflexPointFromLine(const Line& axis, Point& point) const;
public:
	virtual double perimeter() const = 0; // P
	virtual double area() const = 0; // S
	virtual bool operator==(const Shape& another) const = 0; // совпадает ли эта фигура с другой
	virtual bool operator!=(const Shape& another) const = 0;
	virtual bool isCongruentTo(const Shape& another) const = 0; // равна ли эта фигура другой в геометрическом смысле
	virtual bool isSimilarTo(const Shape& another) const = 0; // подобна ли эта фигура другой
	virtual bool containsPoint(const Point& point) const = 0; // находится ли точка внутри фигуры. 
	virtual void rotate(const Point& center, double angle) = 0; //  поворот на угол (в градусах, против часовой стрелки)
	virtual void reflex(const Point& center) = 0; // симметрию относительно точки
	virtual void reflex(const Line& axis) = 0; // симметрию относительно прямой
	virtual void scale(Point center, double coefficient) = 0; // гомотетию с коэффициентом coefficient и центром center.
	virtual ~Shape(){}
};