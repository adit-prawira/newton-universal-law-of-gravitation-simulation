#include "app.hpp"
#include "celestial_body.hpp"
#include "constant.hpp"

// std
#include<array>
namespace newton{
  // Publics
  App::App(const std::string name): window(sf::VideoMode({App::WINDOW_WIDTH, App::WINDOW_HEIGHT}), name){}
  void App::run(){
    this->window.setFramerateLimit(App::FRAME_LIMIT);
    
    entities::CelestialBody earth;
    entities::CelestialBody moon;
    entities::CelestialBody satellite;
    
    earth.setMass(constants::MASS_OF_EARTH_KG)
      .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_EARTH_KG))
      .setPosition({App::WINDOW_WIDTH/2 - 100, App::WINDOW_HEIGHT/2 - 100})
      .setVelocity({0.0f, 0.0f})
      .build();

    moon.setMass(constants::MASS_OF_MOON_KG)
      .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_MOON_KG))
      .setPosition({App::WINDOW_WIDTH/2 - 200, App::WINDOW_HEIGHT/2 - 20})
      .setVelocity({0.0f, -30.36067977f})
      .build();

    satellite.setMass(constants::MASS_OF_MOON_KG)
      .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_MOON_KG))
      .setPosition({App::WINDOW_WIDTH/2 + 200, App::WINDOW_HEIGHT/2 - 20})
      .setVelocity({0.0f, 30.36067977f})
      .build();

    while(this->window.isOpen()){
      while(const std::optional event = this->window.pollEvent()){
        if(event->is<sf::Event::Closed>()){
          this->window.close();
        }
      }
      this->window.clear(sf::Color::Black);
      
      // moon.move(satellite);
      moon.move(earth); 
      // earth.move(moon); 

      // satellite.move(moon);
      // satellite.move(earth);

      this->drawCircle(earth.getRadius(), earth.getPosition(), sf::Color::Green);
      this->drawCircle(moon.getRadius(), moon.getPosition(), sf::Color::Magenta);
      this->drawCircle(satellite.getRadius(), satellite.getPosition(), sf::Color::Cyan);

      sf::Vertex moonVertex{moon.getCenter(), sf::Color::Red};
      sf::Vertex earthVertex{earth.getCenter(), sf::Color::Red};
      std::array lines = {
        moonVertex,
        earthVertex
      };
  
      this->window.draw(lines.data(), lines.size(), sf::PrimitiveType::Lines);

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