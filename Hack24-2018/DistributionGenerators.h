#pragma once
#include <random>
#include <memory>
#include <SFML/Graphics.hpp>

class DistributionGenerators {
public:
	static std::uniform_int_distribution<int>	starSeedDist;
	static std::uniform_int_distribution<int>	numberOfPlanetsDist;
	static std::uniform_int_distribution<int>	planetsDistanceDist;
	static std::uniform_int_distribution<int>	planetSpeedDist;
	static std::uniform_int_distribution<int>	charDist;
	static std::uniform_int_distribution<int>	lengthOfNameDist;

	static sf::Color							starColorDist(std::mt19937& eng);
	static sf::Color							planetColorDist(std::mt19937& eng);
	static int									planetRadiusDist(std::mt19937& eng);

	static void									alienDist(std::mt19937 & eng, std::shared_ptr<sf::Texture> alienTex, std::shared_ptr<sf::RenderTexture>);

private:
	static std::uniform_int_distribution<int>	starColorDistInternal;
	static std::uniform_int_distribution<int>	planetColorDistInternal;
	static std::uniform_int_distribution<int>	planetPositionDistInternal;
	static std::uniform_int_distribution<int>	planetRadiusDistInternal;
	static std::uniform_int_distribution<int>	alienEarsDistInternal;
	static std::uniform_int_distribution<int>	alienEyesDistInternal;
	static std::uniform_int_distribution<int>	alienMouthDistInternal;
	static std::uniform_int_distribution<int>	alienBodyDistInternal;

	static sf::Texture&							alienEarsDist(std::mt19937& eng);
	static sf::Texture&							alienEyesDist(std::mt19937& eng);
	static sf::Texture&							alienMouthDist(std::mt19937& eng);
	static sf::Texture&							alienBodyDist(std::mt19937& eng);
};
