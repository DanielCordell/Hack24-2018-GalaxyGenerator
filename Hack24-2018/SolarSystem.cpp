#define _USE_MATH_DEFINES
#include <cmath>

#include "SolarSystem.h"
#include "DistributionGenerators.h"
#include "PointManipulation.h"
#include "Constants.h"

SolarSystem::SolarSystem(unsigned seed, sf::Color color) : eng(seed), sun(300,70) {
	sun.setFillColor(color);
	sun.setOutlineColor(sf::Color::White);
	sun.setOutlineThickness(5);
	sun.setOrigin(300, 300);
	sun.setPosition(CENTRE);
	int numberOfPlanets = DistributionGenerators::numberOfPlanetsDist(eng);
	for (int i = 0; i < numberOfPlanets; ++i) {
		planets.push_back(Planet(DistributionGenerators::planetColorDist(eng), { 500.f , 500.f - (i+1) * 80.f },DistributionGenerators::planetRadiusDist(eng),DistributionGenerators::planetSpeedDist(eng),DistributionGenerators::starSeedDist(eng)));
	}
}

void SolarSystem::update(sf::Time t) {
	for (Planet& p : planets) {
		auto position = p.GetPosition();
		p.SetPosition(PointManip::RotatePointAroundCentre(position, M_PI/50.f * t.asSeconds() * p.GetSpeed(), false));
	}
}

std::optional<std::shared_ptr<Planet>> SolarSystem::detectClick(const sf::Vector2f& vector2) {
	for (Planet& p : planets) {
		if (p.getBounds().contains(vector2)) return std::make_optional(std::make_shared<Planet>(p));
	}
	return {};
}

void SolarSystem::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(sun, states);
	for (Planet p : planets) {
		target.draw(p, states);
	}
}
