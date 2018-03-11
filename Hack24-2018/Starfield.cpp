#define _USE_MATH_DEFINES
#include <cmath>

#include "Starfield.h"
#include "poissonDiskSampling.hpp"
#include "Constants.h"
#include "PointManipulation.h"

Starfield::Starfield(unsigned seed) : starShape(NUMBER_OF_ARMS * 2) {

	for (int i = 0; i < NUMBER_OF_ARMS * 2; ++i) {
		starShape.setPoint(i, PointManip::MovePointInDirection(CENTRE, i *  M_PI / NUMBER_OF_ARMS, i % 2 ? 130 : 500));
	}
	auto sPoss = thinks::poissonDiskSampling(STAR_SIZE * 2, std::array<float, 2>{STAR_SIZE, STAR_SIZE}, std::array<float, 2>{WINDOW_SIZE - STAR_SIZE, WINDOW_SIZE - STAR_SIZE}, 30.f, seed);
	for (std::array<float, 2> pos : sPoss) {
		Star star(rand(), pos);
		if (IsValidStar(star)) {
			auto starPos = star.getPosition();
			star.setPosition(PointManip::RotatePointAroundCentre(starPos, PointManip::DistanceToCentre(starPos)/500.f * M_PI, false));
			starfield.push_back(star);
		}
	}

	//2nd pass
	for (int i = 0; i < NUMBER_OF_ARMS * 2; ++i) {
		starShape.setPoint(i, PointManip::MovePointInDirection(CENTRE, i *  M_PI / NUMBER_OF_ARMS, i % 2 ? 300 : 500));
	}
	sPoss = thinks::poissonDiskSampling(STAR_SIZE * 5, std::array<float, 2>{STAR_SIZE, STAR_SIZE}, std::array<float, 2>{WINDOW_SIZE - STAR_SIZE, WINDOW_SIZE - STAR_SIZE}, 30.f, seed+1);
	for (std::array<float, 2> pos : sPoss) {
		Star star(rand(), pos);
		if (IsValidStar(star)) {
			auto starPos = star.getPosition();
			star.setPosition(PointManip::RotatePointAroundCentre(starPos, PointManip::DistanceToCentre(starPos) / 500.f * M_PI + M_PI/6.f, false));
			starfield.push_back(star);
		}
	}
}

void Starfield::update(sf::Time t) {
	for (Star& s : starfield) {
		auto position = s.getPosition();
		s.setPosition(PointManip::RotatePointAroundCentre(position, M_PI / 100.f * t.asSeconds(), true));
	}
}

std::optional<Star> Starfield::detectClick(const sf::Vector2f & vector2)
{
	for (Star s : starfield) {
		if (s.getBounds().contains(vector2)) return std::make_optional(s);
	}
	return {};
}

void Starfield::draw(sf::RenderTarget & target, sf::RenderStates states) const {

	for (auto& s : starfield) {
		target.draw(s, states);
	}
}

//If is inside the 6 sided star shape
bool Starfield::IsValidStar(Star& star) const {
	int intersectCount = 0;
	sf::Vector2f p1 = star.getPosition();
	sf::Vector2f q1(WINDOW_SIZE, p1.y);

	for (int i = 0; i < NUMBER_OF_ARMS * 2; ++i) {
		auto p2 = starShape.getPoint(i);
		auto q2 = starShape.getPoint(i == (NUMBER_OF_ARMS * 2 - 1) ? 0 : i + 1);

		int o1 = PointManip::orientation(p1, q1, p2);
		int o2 = PointManip::orientation(p1, q1, q2);
		int o3 = PointManip::orientation(p2, q2, p1);
		int o4 = PointManip::orientation(p2, q2, q1);

		if (o1 != o2 && o3 != o4){
			intersectCount++;
			continue;
		}

		if (o1 == 0 && PointManip::onSegment(p1, p2, q1)) intersectCount++;
		else if (o2 == 0 && PointManip::onSegment(p1, q2, q1)) intersectCount++;
		else if (o3 == 0 && PointManip::onSegment(p2, p1, q2)) intersectCount++;
		else if (o4 == 0 && PointManip::onSegment(p2, q1, q2)) intersectCount++;
	}
	return intersectCount % 2 == 1;

}
