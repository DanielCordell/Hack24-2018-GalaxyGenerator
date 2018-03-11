#pragma once
#include <SFML/Graphics/Texture.hpp>

class ResourceHandler
{
private:
	static std::vector<sf::Texture> mouthTextures;
	static std::vector<sf::Texture> eyeTextures;
	static std::vector<sf::Texture> earTextures;
	static std::vector<sf::Texture> baseTextures;

	static std::vector<std::string> base;

	static std::vector<std::string> ears;

	static std::vector<std::string> eyes;

	static std::vector<std::string> mouth;
public:
	static void Init();
	static sf::Texture& getBody(int i);
	static sf::Texture& getEars(int i);
	static sf::Texture& getEyes(int i);
	static sf::Texture& getMouth(int i);
};
