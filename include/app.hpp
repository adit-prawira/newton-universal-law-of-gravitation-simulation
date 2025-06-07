#pragma once
#include <SFML/Graphics.hpp>
#include "celestial_body.hpp"

// std
#include<string>
#include <unordered_map>
namespace newton{
  class App{
    public:
      App(const std::string name);

      void run();

    private:
      sf::RenderWindow window;
      sf::Font font;
      // sf::Music music;
      void initialize(entities::CelestialBody solarSystem, std::vector<entities::CelestialBody>& celestialBodies, std::unordered_map<std::string, entities::CelestialBody>& celestialBodyRegistry);
      void drawCelestialBody(entities::CelestialBody celestialBody);
      void drawCelestialBodyPaths(entities::CelestialBody celestialBody);

      void drawStatistics(entities::CelestialBody celestialBody, int index);
    };
}