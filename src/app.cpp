#include "app.hpp"
#include "celestial_body.hpp"
#include "constant.hpp"

// std
#include<array>
#include <iostream>

namespace newton{
  // Publics
  App::App(const std::string name): window(sf::VideoMode({App::WINDOW_WIDTH, App::WINDOW_HEIGHT}), name){}
  void App::run(){
    this->window.setFramerateLimit(App::FRAME_LIMIT);

    entities::CelestialBody sun;
    entities::CelestialBody mercury;
    entities::CelestialBody venus;
    entities::CelestialBody earth;
    entities::CelestialBody mars;
    entities::CelestialBody jupiter;

    
    sun.setMass(constants::MASS_OF_SUN_KG)
      .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_SUN_KG))
      .setPosition({App::WINDOW_WIDTH/2 - 100, App::WINDOW_HEIGHT/2 - 100})
      .setVelocity({0.0f, -2.0f})
      .setIsStatic(true)
      .build();
    
    mercury.setMass(constants::MASS_OF_MERCURY_KG)
      .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_MERCURY_KG))
      .setPosition({App::WINDOW_WIDTH/2 - 180, App::WINDOW_HEIGHT/2 - 100})
      .setVelocity({0.0f, -90.0f})
      .setIsStatic(false)
      .build();

    venus.setMass(constants::MASS_OF_VENUS_KG)
      .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_VENUS_KG))
      .setPosition({App::WINDOW_WIDTH/2 - 290, App::WINDOW_HEIGHT/2 - 100})
      .setVelocity({0.0f, -67.0f})
      .setIsStatic(false)
      .build();

    earth.setMass(constants::MASS_OF_EARTH_KG)
      .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_EARTH_KG))
      .setPosition({sun.getCenter().x - 400, sun.getCenter().y})
      .setVelocity({0.0f, -60.0f})
      .setIsStatic(false)
      .build();
    mars.setMass(constants::MASS_OF_MARS_KG)
      .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_MARS_KG))
      .setPosition({sun.getCenter().x - 520, sun.getCenter().y})
      .setVelocity({0.0f, -50.0f})
      .setIsStatic(false)
      .build();
    jupiter.setMass(constants::MASS_OF_JUPITER_KG)
      .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_JUPITER_KG))
      .setPosition({sun.getCenter().x - 650, sun.getCenter().y})
      .setVelocity({0.0f, -43.0f})
      .setIsStatic(false)
      .build();

    while(this->window.isOpen()){
      while(const std::optional event = this->window.pollEvent()){
        if(event->is<sf::Event::Closed>()){
          this->window.close();
        }
      }
      this->window.clear(sf::Color::Black);
      
      mercury.revolve(sun);
      venus.revolve(sun);
      earth.revolve(sun);
      mars.revolve(sun);
      jupiter.revolve(sun);

      this->drawCircle(sun.getRadius(), sun.getPosition(), sf::Color(255, 244, 232));
      this->drawCircle(mercury.getRadius(), mercury.getPosition(), sf::Color(139, 69, 19));
      this->drawCircle(venus.getRadius(), venus.getPosition(), sf::Color::Yellow);
      this->drawCircle(earth.getRadius(), earth.getPosition(), sf::Color(34, 139, 87));
      this->drawCircle(mars.getRadius(), mars.getPosition(), sf::Color::Red);
      this->drawCircle(jupiter.getRadius(), jupiter.getPosition(), sf::Color(255, 153, 102));

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