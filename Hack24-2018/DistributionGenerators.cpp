#include "DistributionGenerators.h"
#include <SFML/Graphics/Color.hpp>
#include "ResourceHandler.h"

sf::Color DistributionGenerators::starColorDist(std::mt19937& eng)
{
	int result = starColorDistInternal(eng);
	sf::Color colorResult;
	switch(result) {
	case 0:
		colorResult = sf::Color(255, 252, 127);
		break;
	case 1:
		colorResult = sf::Color(157, 180, 255);
		break;
	case 2:
		colorResult = sf::Color(175, 195, 255);
		break;
	case 3:
		colorResult = sf::Color(228, 232, 255);
		break;
	case 4:
		colorResult = sf::Color(251, 248, 255);
		break;
	case 5:
		colorResult = sf::Color(255, 244, 232);
		break;
	case 6:
		colorResult = sf::Color(255, 235, 209);
		break;
	case 7:
		colorResult = sf::Color(255, 215, 174);
		break;
	case 8:
		colorResult = sf::Color(255, 198, 144);
		break;
	}
	return colorResult;
}

sf::Color DistributionGenerators::planetColorDist(std::mt19937& eng) {
	int result = planetColorDistInternal(eng);
	int variation = planetColorDistInternal(eng);
	sf::Color colorResult;
	switch(result) {
	case 1:
		colorResult = sf::Color(171 + variation, 101 + variation, 24 + variation); // Venus Brown
		break;
	case 2:
		colorResult = sf::Color(0 + variation, 119 + variation, 190 + variation); // Earth Blue
		break;
	case 3:
		colorResult = sf::Color(57 + variation, 118 + variation, 40 + variation); // Earth Green
		break;
	case 4:
		colorResult = sf::Color(193 + variation, 68 + variation, 14 + variation); // Mars Orange
		break;
	case 5:
		colorResult = sf::Color(253 + variation, 229 + variation, 34 + variation); // Saturn Yellow
		break;
	case 6:
		colorResult = sf::Color(209 + variation, 231 + variation, 231 + variation); // Uranus Blue
		break;
	case 7:
		colorResult = sf::Color(173 + variation, 255 + variation, 47 + variation); // Green
		break;
	case 8:
		colorResult = sf::Color(105 + variation, 68 + variation, 137 + variation); // Purple
		break;
	default:
		colorResult = sf::Color::Magenta;
		break;
	}

	return colorResult;
}

int DistributionGenerators::planetRadiusDist(std::mt19937 & eng)
{
	return planetRadiusDistInternal(eng) * 8;
}

void DistributionGenerators::alienDist(std::mt19937 & eng, std::shared_ptr<sf::Texture> alienTex, std::shared_ptr<sf::RenderTexture> alienRenderTexture) {
	alienRenderTexture->create(128,128);
	alienRenderTexture->clear();
	sf::Sprite s;

	sf::Texture& base = DistributionGenerators::alienBodyDist(eng);
	s.setTexture(base);
	alienRenderTexture->draw(s);

	sf::Texture& ears = DistributionGenerators::alienEarsDist(eng);
	s.setTexture(ears);
	alienRenderTexture->draw(s);

	sf::Texture& eyes = DistributionGenerators::alienEyesDist(eng);
	s.setTexture(eyes);
	alienRenderTexture->draw(s);

	sf::Texture& mouth = DistributionGenerators::alienMouthDist(eng);
	s.setTexture(mouth);
	alienRenderTexture->draw(s);
	alienRenderTexture->display();
	*alienTex = alienRenderTexture->getTexture();
}

sf::Texture& DistributionGenerators::alienEarsDist(std::mt19937& eng) {
	return ResourceHandler::getEars(alienEarsDistInternal(eng));
}

sf::Texture& DistributionGenerators::alienEyesDist(std::mt19937 & eng) {
	return ResourceHandler::getEyes(alienEyesDistInternal(eng));
}

sf::Texture& DistributionGenerators::alienMouthDist(std::mt19937 & eng) {
	return ResourceHandler::getMouth(alienMouthDistInternal(eng));
}

sf::Texture& DistributionGenerators::alienBodyDist(std::mt19937 & eng) {
	return ResourceHandler::getBody(alienBodyDistInternal(eng));
}

std::uniform_int_distribution<int> DistributionGenerators::starSeedDist;
std::uniform_int_distribution<int> DistributionGenerators::numberOfPlanetsDist{ 1,7 };
std::uniform_int_distribution<int> DistributionGenerators::planetsDistanceDist{ 1,8 };
std::uniform_int_distribution<int> DistributionGenerators::starColorDistInternal{ 0,8 };
std::uniform_int_distribution<int> DistributionGenerators::planetColorDistInternal{ 1,8 };
std::uniform_int_distribution<int> DistributionGenerators::planetRadiusDistInternal{ 2,7 };
std::uniform_int_distribution<int> DistributionGenerators::planetSpeedDist{ 1,10 };
std::uniform_int_distribution<int> DistributionGenerators::alienEarsDistInternal{0,8};
std::uniform_int_distribution<int> DistributionGenerators::alienEyesDistInternal{0,8};
std::uniform_int_distribution<int> DistributionGenerators::alienMouthDistInternal{0,8};
std::uniform_int_distribution<int> DistributionGenerators::alienBodyDistInternal{0,9};
std::uniform_int_distribution<int> DistributionGenerators::charDist{ 65,90 };
std::uniform_int_distribution<int> DistributionGenerators::lengthOfNameDist{ 4,10 };


