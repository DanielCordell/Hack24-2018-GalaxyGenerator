#include "ResourceHandler.h"

void ResourceHandler::Init()
{
	for (auto s : base) {
		sf::Texture tex;
		tex.loadFromFile("Resources/" + s);
		baseTextures.push_back(tex);
	}
	for (auto s : ears) {
		sf::Texture tex;
		tex.loadFromFile("Resources/" + s);
		earTextures.push_back(tex);
	}
	for (auto s : eyes) {
		sf::Texture tex;
		tex.loadFromFile("Resources/" + s);
		eyeTextures.push_back(tex);
	}
	for (auto s : mouth) {
		sf::Texture tex;
		tex.loadFromFile("Resources/" + s);
		mouthTextures.push_back(tex);
	}
}

sf::Texture & ResourceHandler::getBody(int i)
{
	return baseTextures.at(i);
}

sf::Texture & ResourceHandler::getEars(int i)
{
	return earTextures.at(i);
}

sf::Texture & ResourceHandler::getEyes(int i)
{
	return eyeTextures.at(i);
}

sf::Texture & ResourceHandler::getMouth(int i)
{
	return mouthTextures.at(i);
}


std::vector<sf::Texture> ResourceHandler::mouthTextures;
std::vector<sf::Texture> ResourceHandler::eyeTextures;
std::vector<sf::Texture> ResourceHandler::earTextures;
std::vector<sf::Texture> ResourceHandler::baseTextures;


std::vector<std::string> ResourceHandler::base{
	"Base_DarkBlue.png",
	"Base_DarkGreen.png",
	"Base_Green.png",
	"Base_LightBlue.png",
	"Base_Orange.png",
	"Base_Purple.png",
	"Base_PurpleRed.png",
	"Base_Red.png",
	"Base_White.png",
	"Base_Yellow.png"

};

std::vector<std::string> ResourceHandler::ears{
	"Ears_Black.png",
	"Ears_DarkBlue.png",
	"Ears_DarkGreen.png",
	"Ears_Green.png",
	"Ears_LightBlue.png",
	"Ears_Orange.png",
	"Ears_Red.png",
	"Ears_White.png",
	"Ears_Yellow.png"
};

std::vector<std::string> ResourceHandler::eyes{
	"Eyes_Alien.png",
	"Eyes_DarkBlue.png",
	"Eyes_Green.png",
	"Eyes_LightBlue.png",
	"Eyes_Orange.png",
	"Eyes_Pink.png",
	"Eyes_Purple.png",
	"Eyes_Red.png",
	"Eyes_White.png"
};

std::vector<std::string> ResourceHandler::mouth{
	"Mouth_CircleLarge.png",
	"Mouth_CircleSmall.png",
	"Mouth_Diamond.png",
	"Mouth_ParallelogramLeft.png",
	"Mouth_ParallelogramRight.png",
	"Mouth_TrapezoidHappy.png",
	"Mouth_TrapezoidSad.png",
	"Mouth_TriangleLeft.png",
	"Mouth_TriangleRight.png"
};