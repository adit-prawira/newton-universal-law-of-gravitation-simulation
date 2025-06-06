#include <SFML/Graphics.hpp>

// std
#include <vector>
#include <random>

namespace generators { 
  struct StarMeta {
    sf::Vector2f position;
    sf::Color color;
    float radius;
  };

  class StarsGenerator {
    public:
      StarsGenerator();
      std::vector<StarMeta> generate(unsigned int total);

    private:  
      std::default_random_engine engine;
      std::uniform_real_distribution<float> getPositionX;
      std::uniform_real_distribution<float> getPositionY;
      std::uniform_real_distribution<float> getRadius; 
      std::uniform_real_distribution<float> getBrightness;   
  };
}