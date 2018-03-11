#include <array>

#include "Star.h"
#include "DistributionGenerators.h"
#include "Constants.h"

Star::Star(unsigned seed, std::array<float, 2> pos): starSeed(seed), eng(seed) {
	starShape.setOutlineColor(sf::Color::Black);
	starShape.setOutlineThickness(2);
	starShape.setRadius(STAR_SIZE/2.f);
	starShape.setPosition(pos[0], pos[1]);
	starShape.setFillColor(DistributionGenerators::starColorDist(eng));

}

void Star::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(starShape, states);
}
