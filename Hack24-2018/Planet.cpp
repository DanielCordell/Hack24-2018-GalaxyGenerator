#include "Planet.h"
#include "DistributionGenerators.h"
#include <iostream>

Planet::Planet(sf::Color color, sf::Vector2f position, int radius, int speed, unsigned seed) : planetCircle(radius), orbitSpeed(speed), eng(seed), alienTex(nullptr), alienRenderTex(nullptr) {
	alienRenderTex = std::make_shared<sf::RenderTexture>();
	alienTex = std::make_shared<sf::Texture>();
	DistributionGenerators::alienDist(eng, alienTex, alienRenderTex);
	planetCircle.setOrigin(radius, radius);
	planetCircle.setPosition(position);
	planetCircle.setFillColor(color);
	planetCircle.setOutlineColor(sf::Color::Black);
	planetCircle.setOutlineThickness(2);

	int planetNameLength = DistributionGenerators::lengthOfNameDist(eng);
	for (int i = 0; i < planetNameLength; i++) {
		planetName += DistributionGenerators::charDist(eng);
	}

	if (radius <= 24) planetType = "Dwarf";
	else if (radius >= 48) planetType = "Gas Giant";
	else planetType = "Terrestrial";
}

std::shared_ptr<sf::Texture> Planet::GetAlienTexture() {
	return alienTex;
}

void Planet::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(planetCircle, states);
}
