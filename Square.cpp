#include "Square.h"

Circle Square::circumscribedCircle() const
{
	double radius = sqrt((vertices[0].x - vertices[2].x) * (vertices[0].x - vertices[2].x) +
		(vertices[0].y - vertices[2].y) * (vertices[0].y - vertices[2].y));
	return Circle(center(), radius);
}

Circle Square::inscribedCircle() const
{
	double radius = sqrt((vertices[0].x - vertices[1].x) * (vertices[0].x - vertices[1].x) +
		(vertices[0].y - vertices[1].y) * (vertices[0].y - vertices[1].y));
	return Circle(center(), radius);
}