#pragma once
#include <SFML/Graphics.hpp>

// std
#include <string>
#include <vector>

namespace entities{
  class CelestialBody {
    public:
      CelestialBody& setMass(float mass);
      CelestialBody& setRadius(float radius);
      CelestialBody& setPosition(sf::Vector2f position);
      CelestialBody& setVelocity(sf::Vector2f velocity);
      CelestialBody& setColor(sf::Color color);
      CelestialBody& setIsStatic(bool isStatic);
      CelestialBody& build();

      float getRadius();
      sf::Vector2f getVelocity();
      sf::Vector2f getPosition();
      sf::Color getColor();
      sf::Vector2f getCenter();
      std::vector<sf::Vertex> getPaths();
      sf::Vertex* getPathVertices();

      float getMass();

      void revolve(CelestialBody otherCelestialBody);
      void updatePath();
      static float massToRadius(float mass);

    private:
      float mass;
      float radius;
      bool isStatic;
      std::vector<sf::Vertex> paths;
      std::vector<sf::Vertex> cachedPaths;
      sf::Color color;
      sf::Vector2f acceleration;
      sf::Vector2f position; 
      sf::Vector2f velocity;
      std::string compileValidationMessages(std::vector<std::string> validationMessages);
  };
}