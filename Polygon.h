#pragma once
#include "Shape.h"
#include <vector>
#include <cassert>

class Polygon : public Shape
{
private:
	bool _isEqual(double a, double b) const
	{
		return a - b <= 1e-9 && b - a <= 1e-9;
	}
	bool _isEqual(const Point& a, const Point& b) const
	{
		return a == b;
	}
	template <class T>
	bool _compareVector(const std::vector<T>& a, const std::vector<T>& b, unsigned int* index_of_comapration = nullptr) const
	{
		if (index_of_comapration) *index_of_comapration = a.size();
		if (a.size() != b.size())
			return false;
		if (a.size() == 0)
			return true;
		unsigned int size = a.size();
		for (unsigned int i = 0; i < size; ++i)
		{
			if (_isEqual(a[0], b[i]))
			{
				if (index_of_comapration) *index_of_comapration = i;
				bool is_equal = true;
				for (unsigned int j = 0; j < size; ++j)
				{
					if (!_isEqual(a[j], b[(j + i) % size]))
					{
						is_equal = false;
						break;
					}
				}
				if (is_equal)
					return true;
				is_equal = true;
				for (unsigned int j = 0; j < size; ++j)
				{
					if (!_isEqual(a[j], b[((size + i) - j) % size]))
					{
						is_equal = false;
						break;
					}
				}
				if (is_equal)
					return true;
			}
		}
		if (index_of_comapration) *index_of_comapration = size;
		return false;
	}
	std::vector<double> _findLengthEdge() const;
	double _findAngle(Point a, Point b, Point c) const;
	std::vector<double> _findAngles() const;
protected:
	std::vector<Point> vertices;
public:
	unsigned int verticesCount() const { return vertices.size(); }
	std::vector<Point> getVertices() const { return vertices; }
	explicit Polygon(std::vector<Point> vertices) : vertices(vertices){}
	template<typename... T>
	explicit Polygon(const T& ... args)
	{
		auto list = std::initializer_list<Point>{ args... };
		vertices.reserve(list.size());
		for (auto&& p : list)
			vertices.push_back(p);
	}
	explicit Polygon(){}
	double perimeter() const;
	double area() const;
	bool isConvex() const; // выпуклый ли
	bool operator==(const Shape& another) const;
	bool operator!=(const Shape& another) const;
	bool isSimilarTo(const Shape& another) const; // подобие
	bool isCongruentTo(const Shape& another) const; // равна ли эта фигура другой в геометрическом смысле
	bool containsPoint(const Point& point) const;
	void rotate(const Point& center, double angle);
	void reflex(const Point& center);
	void scale(Point center, double coefficient); // гомотетию с коэффициентом coefficient и центром center.
	void reflex(const Line& axis); // симметрию относительно прямой
};