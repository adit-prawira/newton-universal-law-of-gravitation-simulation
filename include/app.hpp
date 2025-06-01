#pragma once
#include <SFML/Graphics.hpp>

// std
#include<string>

namespace newton{
  class App{
    public:
      App(const std::string name);

      void run();
      static constexpr int WINDOW_WIDTH = 1080;
      static constexpr int WINDOW_HEIGHT = 800;
      static constexpr int FRAME_LIMIT = 60;  
    private:
      sf::RenderWindow window;

      void drawCircle(float radius, sf::Vector2f position, sf::Color color);

    };
}