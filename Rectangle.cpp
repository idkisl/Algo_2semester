#include "Rectangle.h"

Point Rectangle::center() const
{
	double delta_x = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) / 4;
	double delta_y = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) / 4;
	return Point(delta_x, delta_y);
}

std::pair<Line, Line> Rectangle::diagonals() const
{
	Line d1(vertices[0], vertices[2]);
	Line d2(vertices[1], vertices[3]);
	std::pair<Line, Line> pair(d1, d2);
	return pair;
}

Rectangle::Rectangle(const Point& a, const Point& c, double k)
{
	Point min = a.x > c.x ? c : a;
	Point max = a.x > c.x ? a : c;
	if (k > 1)
		k = 1 / k;

	double tg_alf = ((max.y - min.y) - (max.x - min.x) * k) / (k * (max.y - min.y) - (max.x - min.x));
	double alf = k * (max.y - min.y) == (max.x - min.x) ? M_PI / 2: atan(tg_alf);
	double diangle = sqrt((max.x - min.x) * (max.x - min.x) + (max.y - min.y) * (max.y - min.y));
	double ab = diangle * cos(atan(k));
	double ad = k * ab;
	Point b(min.x + ab * cos(alf), min.y + ab * sin(alf));
	Point d(min.x + ad * sin(alf), min.y + ad * cos(alf));
	vertices.push_back(min);
	vertices.push_back(b);
	vertices.push_back(max);
	vertices.push_back(d);
}
