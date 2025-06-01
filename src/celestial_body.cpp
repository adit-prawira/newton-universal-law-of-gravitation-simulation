#include "celestial_body.hpp"


// std
#include <sstream>
#include <stdexcept>

namespace entities{
  CelestialBody& CelestialBody::setMass(double mass) {
    this->mass = mass;
    return *this;
  }

  CelestialBody& CelestialBody::setRadius(float radius){
    this->radius = radius;
    return *this;
  }

  CelestialBody& CelestialBody::setPosition(sf::Vector2f position){
    this->position = position;
    return *this;
  }

  CelestialBody& CelestialBody::build(){
    std::vector<std::string> validationMessages;
    if(!this->mass) validationMessages.push_back("VALIDATION: Celestial body required mass!");
    if(!this->radius) validationMessages.push_back("VALIDATION: Celestial body required radius!");

    bool hasValidationMessages = !validationMessages.empty();
    if(hasValidationMessages) throw std::runtime_error(this->compileValidationMessages(validationMessages));

    return *this;
  }

  float CelestialBody::getRadius(){
    return this->radius;
  }
  
  sf::Vector2f CelestialBody::getPosition(){
    return this->position;
  }

  //  Privates
  std::string CelestialBody::compileValidationMessages(std::vector<std::string> validationMessages){
    std::ostringstream oss;
    for(size_t i = 0; i < validationMessages.size(); i++){
      oss << validationMessages[i];
      if(i != validationMessages.size() - 1) oss << "\n";
    }
    return oss.str();
  }
}