#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace constants {
  struct PlanetMeta {
    float mass;
    std::string name;
    sf::Vector2f initialVelocity;
    sf::Vector2f initialPosition;
    sf::Color color;
  };
  
  static constexpr int WINDOW_WIDTH = 2160;
  static constexpr int WINDOW_HEIGHT = 1500;
  static constexpr int FRAME_LIMIT = 60;  

  static constexpr float G = 11.6767f;
  static constexpr float PI = 3.141592653589793f;
  static constexpr float MASS_OF_SUN_KG =  100000.0f;
  static constexpr float MASS_OF_MERCURY_KG  = 800.0f;
  static constexpr float MASS_OF_VENUS_KG  = 2000.0f;
  static constexpr float MASS_OF_EARTH_KG  = 5000.0f;
  static constexpr float MASS_OF_MARS_KG  = 1000.0f;
  static constexpr float MASS_OF_JUPITER_KG  = 9000.0f;
  static constexpr float MASS_OF_SATURN_KG  = 7000.0f;
  static constexpr float MASS_OF_URANUS_KG  = 6500.0f;
  static constexpr float MASS_OF_NEPTUNE_KG  = 5500.0f;

  static constexpr int MAX_PATH = 100;
  
  static constexpr float TIME_STEP = 0.05f;

  static constexpr float RHO = 0.1f;

  static constexpr int TOTAL_STARS = 1000;
  static constexpr int MAX_STATISTIC_COLUMNS = 5;
}