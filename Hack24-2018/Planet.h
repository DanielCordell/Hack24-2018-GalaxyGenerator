#pragma once
#include <random>
#include <SFML/Graphics.hpp>
#include <memory>

class Planet : public sf::Drawable {
private:
	sf::CircleShape planetCircle;
	int orbitSpeed;
	std::mt19937 eng;
	std::shared_ptr<sf::Texture> alienTex;
	std::shared_ptr<sf::RenderTexture> alienRenderTex;
	std::string planetName;
	std::string planetType;
public:
	Planet(sf::Color color, sf::Vector2f position, int radius, int speed, unsigned seed);
	int GetSpeed() const { return orbitSpeed; }
	sf::FloatRect getBounds() const { return planetCircle.getGlobalBounds(); }
	sf::Vector2f GetPosition() const { return planetCircle.getPosition(); }
	void SetPosition(sf::Vector2f position) { planetCircle.setPosition(position); }
	std::shared_ptr<sf::Texture> GetAlienTexture();
	std::string GetName() const { return planetName; }
	std::string GetType() const { return planetType; }
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
