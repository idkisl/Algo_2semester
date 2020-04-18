#include "Triangle.h"

Point Triangle::_centerOfCircumscribedCircle() const
{
	Point a = vertices[0];
	Point b = vertices[1];
	Point c = vertices[2];
	double x = (a.y * (b.x * b.x + b.y * b.y - c.x * c.x - c.y * c.y) + b.y * (c.x * c.x + c.y * c.y - a.x * a.x - a.y * a.y) + c.y * (a.x * a.x + a.y * a.y - b.x * b.x - b.y * b.y)) /
		(-2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)));
	double y = (a.x * (b.x * b.x + b.y * b.y - c.x * c.x - c.y * c.y) + b.x * (c.x * c.x + c.y * c.y - a.x * a.x - a.y * a.y) + c.x * (a.x * a.x + a.y * a.y - b.x * b.x - b.y * b.y)) /
		(2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)));
	return Point(x, y);
}

Point Triangle::orthocenter() const
{
	double delta02_x = vertices[2].x - vertices[0].x;
	double delta02_y = vertices[2].y - vertices[0].y;
	double delta12_x = vertices[2].x - vertices[1].x;
	double delta12_y = vertices[2].y - vertices[1].y;
	double delta10_x = vertices[0].x - vertices[1].x;
	double delta10_y = vertices[0].y - vertices[1].y;

	double k1 = (-delta02_x) / (delta02_y);
	double k2 = (-delta12_x) / (delta12_y);
	double k3 = (-delta10_x) / (delta10_y);
	double b1 = vertices[1].y - k1 * vertices[1].x;
	double b2 = vertices[0].y - k2 * vertices[0].x;
	double b3 = vertices[2].y - k3 * vertices[2].x;
	Point center;
	if (delta10_y == 0)
	{
		center.x = (b2 - b3) / (k3 - k2);
		center.y = k3 * center.x + b3;
	}
	else if (delta12_y == 0)
	{
		center.x = (b3 - b1) / (k1 - k3);
		center.y = k1 * center.x + b1;
	}
	else
	{
		center.x = (b2 - b1) / (k1 - k2);
		center.y = k1 * center.x + b1;
	}
	return center;
}

Circle Triangle::circumscribedCircle() const
{
	double S = area();
	double a = (vertices[1].x - vertices[0].x) * (vertices[1].x - vertices[0].x) +
		(vertices[1].y - vertices[0].y) * (vertices[1].y - vertices[0].y);
	double b = (vertices[1].x - vertices[2].x) * (vertices[1].x - vertices[2].x) +
		(vertices[1].y - vertices[2].y) * (vertices[1].y - vertices[2].y);
	double c = (vertices[2].x - vertices[0].x) * (vertices[2].x - vertices[0].x) +
		(vertices[2].y - vertices[0].y) * (vertices[2].y - vertices[0].y);
	double R = sqrt(a * b * c) / (4 * S);
	return Circle(_centerOfCircumscribedCircle(), R);
}

Point Triangle::centroid() const
{
	double x = 0;
	double y = 0;
	for (unsigned int i = 0; i < 3; ++i)
	{
		x += vertices[i].x;
		y += vertices[i].y;
	}
	return Point(x / 3, y / 3);
}

Circle Triangle::inscribedCircle() const
{
	double P = perimeter();
	//find center
	Point A = vertices[0];
	Point B = vertices[1];
	Point C = vertices[2];
	double CA = sqrt((C.x - A.x) * (C.x - A.x) + (C.y - A.y) * (C.y - A.y));
	double CB = sqrt((C.x - B.x) * (C.x - B.x) + (C.y - B.y) * (C.y - B.y));
	double AB = sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
	double r = sqrt((P/2 - AB) * (P/2 - CA) * (P/2 - CB) * 2 / P);
	Point center((CB * A.x + CA * B.x + AB * C.x) / P, (CB * A.y + CA * B.y + AB * C.y) / P);
	return Circle(center, r);
}

Line Triangle::EulerLine() const
{
	return Line(orthocenter(), _centerOfCircumscribedCircle());
}

Circle Triangle::ninePointsCircle() const
{
	double S = area();
	double a = (vertices[1].x - vertices[0].x) * (vertices[1].x - vertices[0].x) +
		(vertices[1].y - vertices[0].y) * (vertices[1].y - vertices[0].y);
	double b = (vertices[1].x - vertices[2].x) * (vertices[1].x - vertices[2].x) +
		(vertices[1].y - vertices[2].y) * (vertices[1].y - vertices[2].y);
	double c = (vertices[2].x - vertices[0].x) * (vertices[2].x - vertices[0].x) +
		(vertices[2].y - vertices[0].y) * (vertices[2].y - vertices[0].y);
	double R = sqrt(a * b * c) / (8 * S);

	Point center1 = _centerOfCircumscribedCircle();
	Point center2 = orthocenter();
	Point center((center1.x + center2.x) / 2, (center1.y + center2.y) / 2);
	return Circle(center, R);
}