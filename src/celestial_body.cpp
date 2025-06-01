#include "celestial_body.hpp"
#include "constant.hpp"

// std
#include <sstream>
#include <stdexcept>

namespace entities{

  CelestialBody& CelestialBody::setMass(float mass) {
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
  
  CelestialBody& CelestialBody::setVelocity(sf::Vector2f velocity){
    this->velocity = velocity;
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

  float CelestialBody::getMass(){
    return this->mass;
  }

  sf::Vector2f CelestialBody::getCenter(){
    return this->position + sf::Vector2f(this->getRadius(), this->getRadius());
  }

  float CelestialBody::getRadius(){
    return this->radius;
  }
  
  sf::Vector2f CelestialBody::getPosition(){
    return this->position;
  }
    
  sf::Vector2f CelestialBody::getVelocity(){
    return this->velocity;
  }

  void CelestialBody::move(CelestialBody otherCelestialBody){
    sf::Vector2f delta;
    sf::Vector2f direction;
    delta = this->getCenter() - otherCelestialBody.getCenter();
    direction = delta.normalized();

    float distance = std::sqrt((delta.x*delta.x) + (delta.y*delta.y));
    sf::Vector2f force = (direction * constants::G * this->mass * otherCelestialBody.getMass())/(distance*distance);
    sf::Vector2f acceleration;
    acceleration = force/this->mass;
    this->velocity += acceleration*constants::TIME_STEP;
    this->position += this->velocity*constants::TIME_STEP;
  }

  float CelestialBody::massToRadius(float mass){
    return std::pow((3*mass)/(4*constants::PI*constants::RHO), (1.0f/3.0f));
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