#pragma once
#include <SFML/System/Vector2.hpp>

#include "Star.h"

namespace PointManip {
	sf::Vector2f MovePointInDirection(sf::Vector2f position, float angleInRad, unsigned distance);
	sf::Vector2f RotatePointAroundCentre(sf::Vector2f point, float angleInRad, bool direction);
	float DistanceToCentre(sf::Vector2f point);

	//Internal
	bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
	//Internal
	int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
}
