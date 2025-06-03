#include "app.hpp"
#include "celestial_body.hpp"
#include "constant.hpp"

// std
#include<array>
#include <iostream>
#include <sstream>

namespace newton{
  // Publics
  App::App(const std::string name): 
  window(sf::VideoMode({App::WINDOW_WIDTH, App::WINDOW_HEIGHT}), name), font("fonts/FiraCode-Regular.ttf"){}
  void App::run(){
    this->window.setFramerateLimit(App::FRAME_LIMIT);
    entities::CelestialBody sun, mercury, venus, earth, mars, jupiter;
    
  sun.setName("Sun")
    .setMass(constants::MASS_OF_SUN_KG)
    .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_SUN_KG))
    .setPosition({App::WINDOW_WIDTH/2 - 100, App::WINDOW_HEIGHT/2 - 100})
    .setVelocity({0.0f, -2.0f})
    .setIsStatic(true)
    .setColor(sf::Color(255, 244, 232))
    .build();
  
  mercury.setName("Mercury")
    .setMass(constants::MASS_OF_MERCURY_KG)
    .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_MERCURY_KG))
    .setPosition({App::WINDOW_WIDTH/2 - 180, App::WINDOW_HEIGHT/2 - 100})
    .setVelocity({0.0f, -90.0f})
    .setIsStatic(false)
    .setColor(sf::Color(139, 69, 19))
    .build();

  venus.setName("Venus")
    .setMass(constants::MASS_OF_VENUS_KG)
    .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_VENUS_KG))
    .setPosition({App::WINDOW_WIDTH/2 - 290, App::WINDOW_HEIGHT/2 - 100})
    .setVelocity({0.0f, -67.0f})
    .setIsStatic(false)
    .setColor(sf::Color::Yellow)
    .build();

  earth.setName("Earth")
    .setMass(constants::MASS_OF_EARTH_KG)
    .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_EARTH_KG))
    .setPosition({sun.getCenter().x - 400, sun.getCenter().y})
    .setVelocity({0.0f, -60.0f})
    .setIsStatic(false)
    .setColor(sf::Color(34, 139, 87))
    .build();

  mars.setName("Mars")
    .setMass(constants::MASS_OF_MARS_KG)
    .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_MARS_KG))
    .setPosition({sun.getCenter().x - 520, sun.getCenter().y})
    .setVelocity({0.0f, -50.0f})
    .setIsStatic(false)
    .setColor(sf::Color::Red)
    .build();

  jupiter.setName("Jupiter").setMass(constants::MASS_OF_JUPITER_KG)
    .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_JUPITER_KG))
    .setPosition({sun.getCenter().x - 650, sun.getCenter().y})
    .setVelocity({0.0f, -44.5f})
    .setIsStatic(false)
    .setColor(sf::Color(255, 153, 102))
    .build(); 

    while(this->window.isOpen()){
      while(const std::optional event = this->window.pollEvent()){
        if(event->is<sf::Event::Closed>()){
          this->window.close();
        }
      }
      this->window.clear(sf::Color::Black);
      
      mercury.revolve(sun);
      mercury.updatePath();

      venus.revolve(sun);
      venus.updatePath();
      
      earth.revolve(sun);
      earth.updatePath();

      mars.revolve(sun);
      mars.updatePath();

      jupiter.revolve(sun);
      jupiter.updatePath();

      this->drawCircle(sun.getRadius(), sun.getPosition(), sun.getColor());
      this->drawCircle(mercury.getRadius(), mercury.getPosition(), mercury.getColor());
      this->drawCircle(venus.getRadius(), venus.getPosition(), venus.getColor());
      this->drawCircle(earth.getRadius(), earth.getPosition(), earth.getColor());
      this->drawCircle(mars.getRadius(), mars.getPosition(), mars.getColor());
      this->drawCircle(jupiter.getRadius(), jupiter.getPosition(), jupiter.getColor());

      this->window.draw(mercury.getPathVertices(), mercury.getPaths().size(), sf::PrimitiveType::Lines);
      this->window.draw(venus.getPathVertices(), venus.getPaths().size(), sf::PrimitiveType::Lines);
      this->window.draw(earth.getPathVertices(), earth.getPaths().size(), sf::PrimitiveType::Lines);
      this->window.draw(mars.getPathVertices(), mars.getPaths().size(), sf::PrimitiveType::Lines);
      this->window.draw(jupiter.getPathVertices(), jupiter.getPaths().size(), sf::PrimitiveType::Lines);
    
      this->drawStatistics(sun, 0);
      this->drawStatistics(mercury, 1);
      this->drawStatistics(venus, 2);
      this->drawStatistics(earth, 3);
      this->drawStatistics(mars, 4);
      this->drawStatistics(jupiter, 5);

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

  void App::drawStatistics(entities::CelestialBody celestialBody, int index){
    std::vector<std::string> infos;
    auto clearStringStream = [](std::stringstream& ss, std::ostringstream& oss){
      ss.str("");
      ss.clear();
      oss.str("");
      oss.clear();
    };

    std::ostringstream oss;
    std::stringstream ss;
    oss << "Planet Name -> " << celestialBody.getName();
    infos.push_back(oss.str());
    clearStringStream(ss, oss);

    ss << std::fixed << std::setprecision(3) << celestialBody.getAngularVelocity();
    oss << "Angular velocity -> " << ss.str() << " rad/s";
    infos.push_back(oss.str());
    clearStringStream(ss, oss);
  
    ss << std::fixed << std::setprecision(3) << celestialBody.getCenter().x;
    std::string xPosition{ss.str()};
    clearStringStream(ss, oss);

    ss << std::fixed << std::setprecision(3) << celestialBody.getCenter().y;
    std::string yPosition{ss.str()};
    clearStringStream(ss, oss);

    oss << "Position -> " << "(" << xPosition << "," << yPosition << ")";
    infos.push_back(oss.str());
    clearStringStream(ss, oss);


    for(size_t j = 0; j < infos.size(); j++){
      sf::Text text(this->font);
      text.setString(infos[j]);
      text.setFillColor(sf::Color::White);
      text.setCharacterSize(12);
      text.setPosition({10.0f + (250.0f*index), j*20.0f + 10.0f});
      this->window.draw(text);
    }
  }
} 