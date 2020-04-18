#include "Polygon.h"

std::vector<double> Polygon::_findLengthEdge() const
{
	std::vector<double> length;
	unsigned int size = vertices.size();
	for (unsigned int i = 0; i < size; ++i)
	{
		double vertex = sqrt((vertices[i].x - vertices[(i + 1) % size].x) * (vertices[i].x - vertices[(i + 1) % size].x) +
			(vertices[i].y - vertices[(i + 1) % size].y) * (vertices[i].y - vertices[(i + 1) % size].y));
		length.push_back(vertex);
	}
	return length;
}

double Polygon::_findAngle(Point a, Point b, Point c) const
{
	double scal = (a.x - b.x) * (c.x - b.x) + (a.y - b.y) * (c.y - b.y); // скалярное произведение ab X bc
	double mod_ab = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); // размер первого вектора
	double mod_bc = sqrt((c.x - b.x) * (c.x - b.x) + (c.y - b.y) * (c.y - b.y)); // размер второго вектора
	double cos = (scal / (mod_ab * mod_bc));
	return acos(cos);
}

std::vector<double> Polygon::_findAngles() const
{
	std::vector<double> angle;
	unsigned int size = vertices.size();
	for (unsigned int i = 0; i < size; ++i)
	{
		angle.push_back(_findAngle(vertices[i], vertices[(i + 1) % size], vertices[(i + 2) % size]));
	}
	return angle;
}

double Polygon::perimeter() const
{
	//assert(vertices.size() < 3, "Polygon perimetr error, incorrect size of vertices, it is not a Polygon");
	if (vertices.size() < 3)
		throw std::runtime_error("Polygon perimetr error, incorrect size of vertices, it is not a Polygon");

	double P = sqrt((vertices[0].x - vertices[vertices.size() - 1].x) * (vertices[0].x - vertices[vertices.size() - 1].x) +
		(vertices[0].y - vertices[vertices.size() - 1].y) * (vertices[0].y - vertices[vertices.size() - 1].y)); // связь последней вершины с первой

	for (unsigned int i = 0; i < vertices.size() - 1; ++i)
	{
		double len = sqrt((vertices[i].x - vertices[i + 1].x) * (vertices[i].x - vertices[i + 1].x) +
			(vertices[i].y - vertices[i + 1].y) * (vertices[i].y - vertices[i + 1].y));
		P += len;
	}
	return P;
}

double Polygon::area() const
{
	unsigned int size = vertices.size();
	double S = 0;
	for (unsigned int i = 0; i < size; ++i)
	{
		S += (vertices[i].x + vertices[(i + 1) % size].x) * (vertices[i].y - vertices[(i + 1) % size].y);
	}
	S = std::abs(S / 2);
	return S;
}

bool Polygon::isConvex() const
{
	//assert(vertices.size() < 3, "Polygon .isConvex() error, incorrect size of vertices, it is not a Polygon");
	//if (vertices.size() < 3)
	//	throw std::runtime_error("Polygon .isConvex() error, incorrect size of vertices, it is not a Polygon");
	unsigned int size = vertices.size();
	float scal;
	bool sign;
	for (unsigned int i = 0; i < size; ++i)
	{
		if (i != 0)
			sign = scal >= 0 ? true : false;
		scal = (vertices[(i + 1) % size].x - vertices[i].x) * (vertices[(i + 2) % size].y - vertices[(i + 1) % size].y) -
			(vertices[(i + 1) % size].y - vertices[i].y) * (vertices[(i + 2) % size].x - vertices[(i + 1) % size].x); // псевдоскалярное произведение
		if (i == 0)
			sign = scal >= 0 ? true : false;
		bool cur_sign = scal >= 0 ? true : false;
		if (cur_sign != sign)
			return false;
	}
	return true;
}

bool Polygon::operator==(const Shape& another) const
{
	const Polygon* other = dynamic_cast<const Polygon*> (&another);
	if (other == nullptr)
		return false;
	return _compareVector(vertices, other->vertices);
}

bool Polygon::operator!=(const Shape& another) const
{
	return !(*this == another);
}

bool Polygon::isSimilarTo(const Shape& another) const
{
	const Polygon* other = dynamic_cast<const Polygon*> (&another);
	if (other == nullptr)
		return false;
	std::vector<double> angle = _findAngles();
	std::vector<double> angle_another = other->_findAngles();
	return _compareVector(angle, angle_another);
}

bool Polygon::isCongruentTo(const Shape& another) const
{
	const Polygon* other = dynamic_cast<const Polygon*> (&another);
	if (other == nullptr)
		return false;
	std::vector<double> angle = _findAngles();
	std::vector<double> angle_another = other->_findAngles();
	unsigned int index_angle;
	bool angle_comaration = _compareVector(angle, angle_another, &index_angle);
	std::vector<double> edge = _findLengthEdge();
	std::vector<double> edge_another = other->_findLengthEdge();
	unsigned int index_edge;
	bool edge_comaration = _compareVector(angle, angle_another, &index_edge);
	if (!angle_comaration || !edge_comaration)
		return false;
	if (index_angle == index_edge)
		return true;
	return false;
}

bool Polygon::containsPoint(const Point& point) const
{
	unsigned int size = vertices.size();
	int count_cross = 0;
	//
	for (unsigned int i = 0; i < size; ++i)
	{
		unsigned int i2 = (i + 1) % size;
		if ((point.y < vertices[i].y && point.y > vertices[i2].y) || (point.y > vertices[i].y && point.y < vertices[i2].y))
		{
			//по разные стороны от луча
			Line ab(vertices[i], vertices[i2]);
			std::pair<double, double> line = (Line(vertices[i], vertices[i2])).returnLine();
			double x = (point.y - line.second) / line.first;
			if (x >= point.x)
				++count_cross;
		}
		if (vertices[i].y == point.y)
		{
			if ((vertices[i2].y >= point.y && vertices[((i + size) - 1) % size].y < point.y) ||
				(vertices[i2].y < point.y && vertices[((i + size) - 1) % size].y > point.y))
				++count_cross;
		}
	}
	if (count_cross % 2 == 1)
		return true;
	return false;
}

void Polygon::rotate(const Point& center, double angle)
{
	angle *= M_PI / 180;
	for (unsigned int i = 0; i < vertices.size(); ++i)
		_rotatePoint(center, vertices[i], angle);
}

void Polygon::reflex(const Point& center)
{
	for (unsigned int i = 0; i < vertices.size(); ++i)
		_reversePoint(center, vertices[i]);
}

void Polygon::scale(Point center, double coefficient)
{
	for (unsigned int i = 0; i < vertices.size(); ++i)
		_scalePoint(center, vertices[i], coefficient);
}

void Polygon::reflex(const Line& axis)
{
	for (unsigned int i = 0; i < vertices.size(); ++i)
		_reflexPointFromLine(axis, vertices[i]);
}