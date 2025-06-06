#include "maths.hpp"

namespace maths {

float Math::cross(const sf::Vector2f &u, const sf::Vector2f &v) {
  return (u.x * v.y) - (u.y * v.x);
}
} // namespace maths
