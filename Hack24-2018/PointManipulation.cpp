#define _USE_MATH_DEFINES

#include <cmath>

#include "PointManipulation.h"
#include "Constants.h"

sf::Vector2f PointManip::MovePointInDirection(sf::Vector2f position, float angleInRad, unsigned distance) {
	position.x += sin(angleInRad) * distance;
	position.y += cos(angleInRad) * distance;
	return position;
}

sf::Vector2f PointManip::RotatePointAroundCentre(sf::Vector2f point, float angleInRad, bool direction) {
	if (direction) angleInRad = -angleInRad;
	float s = sin(angleInRad);
	float c = cos(angleInRad);

	// translate point back to origin:
	point.x -= CENTRE.x;
	point.y -= CENTRE.y;

	// rotate point
	float xnew = point.x * c - point.y * s;
	float ynew = point.x * s + point.y * c;

	// translate point back
	return sf::Vector2f(xnew + CENTRE.x, ynew + CENTRE.y);
}

float PointManip::DistanceToCentre(sf::Vector2f pos) {
	return sqrt(pow(pos.x - CENTRE.x, 2) + pow(pos.y - CENTRE.y, 2));
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool PointManip::onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;

	return false;
}

int PointManip::orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;

	return (val > 0) ? 1 : 2;
}
