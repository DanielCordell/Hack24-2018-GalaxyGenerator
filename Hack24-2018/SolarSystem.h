#pragma once
#include <random>
#include <SFML/Graphics.hpp>
#include "Planet.h"
#include <optional>

class SolarSystem : public sf::Drawable {
private:
	std::vector<Planet> planets;
	std::mt19937 eng;
	sf::CircleShape sun;
	sf::Texture currentTexture;
public:
	SolarSystem(unsigned seed, sf::Color color);
	void update(sf::Time t);
	std::optional<std::shared_ptr<Planet>> detectClick(const sf::Vector2f& vector2);
	int size() const { return planets.size(); }
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
