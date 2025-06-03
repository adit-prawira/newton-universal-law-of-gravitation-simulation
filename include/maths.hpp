#pragma once
#include "SFML/Graphics.hpp"

namespace maths{
  class Math{
    public:
      static float cross(const sf::Vector2f& u, const sf::Vector2f& v);
  };
}