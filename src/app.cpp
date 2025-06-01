#include "app.hpp"
#include "celestial_body.hpp"
#include "constant.hpp"

namespace newton{
  // Publics
  App::App(const std::string name): window(sf::VideoMode({App::WINDOW_WIDTH, App::WINDOW_HEIGHT}), name){}
  void App::run(){
    this->window.setFramerateLimit(App::FRAME_LIMIT);
    
    entities::CelestialBody earth;
    entities::CelestialBody moon;
    earth.setMass(constants::MASS_OF_EARTH_KG)
      .setRadius(100)
      .setPosition({App::WINDOW_WIDTH/2, App::WINDOW_HEIGHT/2})
      .build();

    moon.setMass(constants::MASS_OF_MOON_KG)
      .setRadius(20)
      .setPosition({App::WINDOW_WIDTH/2 - 100, App::WINDOW_HEIGHT/2})
      .build();

    while(this->window.isOpen()){
      while(const std::optional event = this->window.pollEvent()){
        if(event->is<sf::Event::Closed>()){
          this->window.close();
        }
      }
      this->window.clear(sf::Color::Black);
      this->drawCircle(earth.getRadius(), earth.getPosition(), sf::Color::Green);
      this->drawCircle(moon.getRadius(), moon.getPosition(), sf::Color::Magenta);
      this->window.display();
    }
    
  }

  // Privates
  void App::drawCircle(float radius, sf::Vector2f position, sf::Color color){
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setPosition(position);
    circle.setFillColor(color);
    this->window.draw(circle);
  }
} 