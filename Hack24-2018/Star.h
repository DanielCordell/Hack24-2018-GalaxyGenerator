#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Star : public sf::Drawable {
private:
	unsigned starSeed;
	sf::CircleShape starShape;
	std::mt19937 eng;

public:
	Star(unsigned seed, std::array<float, 2> pos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Vector2f getPosition() const { return starShape.getPosition(); }
	void setPosition(sf::Vector2f pos) { starShape.setPosition(pos); }
	sf::FloatRect getBounds() const { return starShape.getGlobalBounds(); }
	unsigned getSeed() const { return starSeed; }
	sf::Color getColor() const { return starShape.getFillColor(); }
};
