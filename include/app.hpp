#pragma once
#include <SFML/Graphics.hpp>
#include "celestial_body.hpp"

// std
#include<string>

namespace newton{
  class App{
    public:
      App(const std::string name);

      void run();
      static constexpr int WINDOW_WIDTH = 2160;
      static constexpr int WINDOW_HEIGHT = 1500;
      static constexpr int FRAME_LIMIT = 60;  
    private:
      sf::RenderWindow window;
      sf::Font font;

      void drawCircle(float radius, sf::Vector2f position, sf::Color color);
      void drawStatistics(entities::CelestialBody celestialBody, int index);
    };
}