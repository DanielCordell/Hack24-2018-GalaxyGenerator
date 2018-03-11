#pragma once
#include <vector>
#include <optional>

#include "Star.h"

class Starfield : public sf::Drawable {
private:
	std::vector<Star> starfield;
	sf::ConvexShape starShape;
	bool IsValidStar(Star& star) const;
public:
	Starfield(unsigned seed);
	void update(sf::Time t);
	auto size() { return starfield.size(); }
	std::optional<Star> detectClick(const sf::Vector2f& vector2);
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
