#pragma once
#include <SFML/Graphics.hpp>

// std
#include <string>
#include <vector>

namespace entities{
  class CelestialBody {
    public:
      CelestialBody& setMass(double mass);
      CelestialBody& setRadius(float radius);
      CelestialBody& setPosition(sf::Vector2f position);
      CelestialBody& build();

      float getRadius();
      sf::Vector2f getPosition();

    private:
      double mass;
      float radius;
      sf::Vector2f position;      
      std::string compileValidationMessages(std::vector<std::string> validationMessages);
  };
}