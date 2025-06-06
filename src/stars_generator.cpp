#include "stars_generator.hpp"
#include "constant.hpp"
namespace generators {
  // Publics
  StarsGenerator::StarsGenerator(): 
    engine(std::random_device{}()),
    getPositionX(0.0f, (float) constants::WINDOW_WIDTH),
    getPositionY(0.0f, (float) constants::WINDOW_HEIGHT),
    getRadius(0.5f, 5.5f),
    getBrightness(150, 255)
  {
  }

  std::vector<StarMeta> StarsGenerator::generate(unsigned int total){
    std::vector<StarMeta> stars;
    for(int i = 0; i < total; i++){
      float x = this->getPositionX(engine);
      float y = this->getPositionY(engine);
      float radius = this->getRadius(engine);
      
      //  cast to integer as the random number can be a float
      auto brightness = (uint8_t) this->getBrightness(engine);
      stars.push_back({
        {x, y},
        {brightness, brightness, brightness},
        radius
      });
    }

    return stars;
  }
}