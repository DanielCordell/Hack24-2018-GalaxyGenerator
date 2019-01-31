#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <memory>
#include <cstdlib>

#include "poissonDiskSampling.hpp"
#include "Starfield.h"
#include "Constants.h"

#include "SolarSystem.h"
#include "ResourceHandler.h"
#include "PointManipulation.h"

int main() {
	ResourceHandler::Init();
	srand(time(nullptr));
	rand();
	int starfieldSeed = rand();
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "No Mans Galaxy Generation Tool", sf::Style::Close, sf::ContextSettings{ 0,0,1 });
	ImGui::SFML::Init(window);
	sf::Clock deltaClock;
	//Only persistant data!
	Starfield starfield(starfieldSeed);

	sf::CircleShape centreofuniverse;
	centreofuniverse.setRadius(30);
	centreofuniverse.setFillColor(sf::Color(50,50,50));
	centreofuniverse.setOrigin(30, 30);
	centreofuniverse.setPosition(500, 500);

	sf::Font font;
	font.loadFromFile("Resources/ALIEE13.TTF");

	//Pointer to the Current SolarSystem (will be deleted)
	SolarSystem* solarSystem = nullptr;

	//Pointer to currently selected planet (will be deleted)
	std::shared_ptr<Planet> planet = nullptr;

	std::shared_ptr<sf::Texture> tex = nullptr;

	bool easterEgg = false;
	sf::Clock eastereggclock;


	sf::Time deltaTime;
	bool starView = true;
	while (window.isOpen()) {
		deltaTime += deltaClock.getElapsedTime();
		if (deltaTime.asSeconds() < (1 / 60.f)) continue;
		if (starView){
			if (solarSystem) {
				delete solarSystem;
				solarSystem = nullptr;
			}
			if (planet) {
				planet = nullptr;
			}


			//STAR VIEW
			sf::Event event;
			while (window.pollEvent(event)) {
				ImGui::SFML::ProcessEvent(event);
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					sf::Vector2f pressCoords{ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
					if (PointManip::DistanceToCentre(pressCoords) < 30) {
						easterEgg = true;
						eastereggclock.restart();
						continue;
					}
					std::optional<Star> clickedStar = starfield.detectClick(pressCoords);
					if (clickedStar.has_value()) {
						starView = false;
						solarSystem = new SolarSystem(clickedStar.value().getSeed(), clickedStar.value().getColor());
						break;
					}
				}
			}
			starfield.update(deltaClock.getElapsedTime());
			if (easterEgg) {
				window.clear();
				if (eastereggclock.getElapsedTime().asSeconds() > 1.f) {
					sf::Text congrats("Congratulations!", font);
					congrats.setOrigin(congrats.getGlobalBounds().width / 2.f, congrats.getGlobalBounds().height / 2.f);
					congrats.setPosition(500, 400);
					window.draw(congrats);
				}
				if (eastereggclock.getElapsedTime().asSeconds() > 2.f) {
					sf::Text youwon("You won!", font);
					youwon.setOrigin(youwon.getGlobalBounds().width / 2.f, youwon.getGlobalBounds().height / 2.f);
					youwon.setPosition(500, 450);
					window.draw(youwon);
				}
				if (eastereggclock.getElapsedTime().asSeconds() > 4.f) {
					sf::Text nothing("Nothing!", font);
					nothing.setOrigin(nothing.getGlobalBounds().width / 2.f, nothing.getGlobalBounds().height / 2.f);
					nothing.setPosition(500, 500);
					window.draw(nothing);

					sf::Text stellar("Stellar Gameplay eh?", font);
					stellar.setOrigin(stellar.getGlobalBounds().width / 2.f, stellar.getGlobalBounds().height / 2.f);
					stellar.setPosition(200, 200);
					stellar.rotate(-30);
					window.draw(stellar);
				}
				if (eastereggclock.getElapsedTime().asSeconds() > 5.f) {
					sf::Text c("Copyright Hello Games", font);
					c.setCharacterSize(20);
					c.setOrigin(c.getGlobalBounds().width / 2.f, c.getGlobalBounds().height / 2.f);
					c.setPosition(500, 530);
					window.draw(c);

					sf::Text stellar("No Mans Sky? More like no FANS sky.", font);
					stellar.setOrigin(stellar.getGlobalBounds().width / 2.f, stellar.getGlobalBounds().height / 2.f);
					stellar.setPosition(700, 800);
					stellar.rotate(30);
					window.draw(stellar);
				}
				if (eastereggclock.getElapsedTime().asSeconds() > 7.f) {
					easterEgg = false;
				}
			}
			else {
				ImGui::SFML::Update(window, deltaClock.restart());
				ImGui::Begin("Number Of Star Systems", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
				ImGui::SetWindowPos({ 10,10 });
				std::string str = "Number Of Star Systems: " + std::to_string(starfield.size()) + "\nClick on a star to view more.";
				ImGui::Text(str.c_str());
				ImGui::End(); // end window

				window.clear(); // fill background with color
				window.draw(centreofuniverse);
				window.draw(starfield);
				ImGui::SFML::Render(window);

			}
			window.display();
		}
		else {
			//PLANET VIEW
			sf::Event event;
			while (window.pollEvent(event)) {
				ImGui::SFML::ProcessEvent(event);
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					sf::Vector2f pressCoords{ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) };
					std::optional<std::shared_ptr<Planet>> clickedPlanet = solarSystem->detectClick(pressCoords);
					if (clickedPlanet.has_value()) {
						planet = clickedPlanet.value();
						tex = planet->GetAlienTexture();
					}
				}
			}

			solarSystem->update(deltaClock.getElapsedTime());
			starfield.update(deltaClock.getElapsedTime());
			ImGui::SFML::Update(window, deltaClock.restart());
			ImGui::Begin("Number Of Planets", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
			ImGui::SetWindowPos({ 10,10 });
			std::string s = "Number of Planets in this Star System: " + std::to_string(solarSystem->size()) + "\nClick on a planet to view more.";
			ImGui::Text(s.c_str());
			ImGui::Spacing();
			if (planet) {
				s = "Planet Name: " + planet->GetName();
				ImGui::Text(s.c_str());
				s = "Planet Type: " + planet->GetType();
				ImGui::Text(s.c_str());
				ImGui::Image(*tex);
				ImGui::Spacing();
			}
			if (ImGui::Button("Back to the Solar System") || sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
				starView = true;
			}
			ImGui::End();

			window.clear();
			window.draw(*solarSystem);


			ImGui::SFML::Render(window);
			window.display();
		}
	}
	ImGui::SFML::Shutdown();
}
