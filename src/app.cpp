#include "app.hpp"
#include "celestial_body.hpp"
#include "constant.hpp"
#include "stars_generator.hpp"
#include <SFML/Audio.hpp>

// std
#include<array>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace newton{
  // Publics
  App::App(const std::string name): 
    window(sf::VideoMode({constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT}), name), 
    font("fonts/FiraCode-Regular.ttf")
    {}
  
  void App::run(){
    sf::Music music("soundtrack/soundtrack.wav"); 
    music.setLooping(true);
    music.play();
    this->window.setFramerateLimit(constants::FRAME_LIMIT);

    entities::CelestialBody sun;
    std::vector<entities::CelestialBody> planets;
    std::unordered_map<std::string, entities::CelestialBody> planetRegistry;

    sun.setName("Sun")
      .setMass(constants::MASS_OF_SUN_KG)
      .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_SUN_KG))
      .setPosition({constants::WINDOW_WIDTH/2 - 100, constants::WINDOW_HEIGHT/2 - 100})
      .setVelocity({0.0f, -2.0f})
      .setColor(sf::Color(255, 215, 128))
      .build();
    this->initialize(sun, planets, planetRegistry);

    generators::StarsGenerator starsGenerator;    
    std::vector<sf::CircleShape> stars;
    for(const auto &starMeta:starsGenerator.generate(constants::TOTAL_STARS)){
      sf::CircleShape star;
      star.setPosition(starMeta.position);
      star.setFillColor(starMeta.color);
      star.setRadius(starMeta.radius);
      stars.push_back(star);
    }

    entities::CelestialBody moon;
    
    moon.setName("Moon")
      .setMass(constants::MASS_OF_MOON_KG)
      .setRadius(entities::CelestialBody::massToRadius(constants::MASS_OF_MOON_KG))
      .setPosition({planetRegistry["Earth"].getCenter().x- 70, planetRegistry["Earth"].getCenter().y})
      .setVelocity({planetRegistry["Earth"].getVelocity().x, planetRegistry["Earth"].getVelocity().y+7.0f})
      .setColor(sf::Color(128, 128, 128))
      .build();

    std::cout << "STARING: Starting solar system simulation..." << std::endl;
    while(this->window.isOpen()){
      while(const std::optional event = this->window.pollEvent()){
        if(event->is<sf::Event::Closed>()){
          std::cout << "EXISTING: Exiting solar system simulation..." << std::endl;
          this->window.close();
        }
      }
      this->window.clear(sf::Color::Black);
  
      for(const auto &star:stars){
        this->window.draw(star);
      }

      for(size_t i = 0; i < planets.size(); i++){
        planets[i].revolve(sun);
        planets[i].updatePath();
        planetRegistry[planets[i].getName()] = planets[i];
      }
      
      this->drawCelestialBody(sun);
      this->drawStatistics(sun, 0);

      this->drawCelestialBody(moon);
      for(size_t i = 0; i < planets.size(); i++){
        this->drawCelestialBody(planets[i]);
        this->drawCelestialBodyPaths(planets[i]);
        this->drawStatistics(planets[i], i+1);
      }

      this->window.display();
    }
  }

  // Privates
  void App::initialize(entities::CelestialBody solarSystem, std::vector<entities::CelestialBody>& celestialBodies, std::unordered_map<std::string, entities::CelestialBody>& celestialBodyRegistry){
    std::cout << "INITIALISING: Preparing solar systems..." << std::endl;
    const std::vector<constants::PlanetMeta> planetMetas = {
      {constants::MASS_OF_MERCURY_KG, "Mercury", {0.0f, -90.0f}, {solarSystem.getCenter().x - 180, solarSystem.getCenter().y}, sf::Color(139, 69, 19)},
      {constants::MASS_OF_VENUS_KG, "Venus", {0.0f, -67.0f}, {solarSystem.getCenter().x - 290, solarSystem.getCenter().y}, sf::Color::Yellow},
      {constants::MASS_OF_EARTH_KG, "Earth", {0.0f, -60.0f}, {solarSystem.getCenter().x - 400, solarSystem.getCenter().y}, sf::Color(34, 139, 87)},
      {constants::MASS_OF_MARS_KG, "Mars", {0.0f, -50.0f}, {solarSystem.getCenter().x - 520, solarSystem.getCenter().y}, sf::Color::Red},
      {constants::MASS_OF_JUPITER_KG, "Jupiter", {0.0f, -44.5f}, {solarSystem.getCenter().x - 650, solarSystem.getCenter().y}, sf::Color(255, 153, 102)},
      {constants::MASS_OF_SATURN_KG, "Saturn", {0.0f, -40.5f}, {solarSystem.getCenter().x - 750, solarSystem.getCenter().y}, sf::Color(210, 180, 140)},
      {constants::MASS_OF_URANUS_KG, "Uranus", {0.0f, -38.5f}, {solarSystem.getCenter().x - 850, solarSystem.getCenter().y}, sf::Color(173, 216, 230)},
      {constants::MASS_OF_NEPTUNE_KG, "Neptune", {0.0f, -36.5f}, {solarSystem.getCenter().x - 950, solarSystem.getCenter().y}, sf::Color(28, 82, 162)}
    };
    
    for(const auto &planetMeta:planetMetas){
      entities::CelestialBody celestialBody;
      std::cout << "\t => Creating: " << planetMeta.name << std::endl;
      std::cout << "\t\t -> Mass: " << planetMeta.mass << std::endl;
      std::cout << "\t\t -> Initial Position Vector: " << "(" << planetMeta.initialPosition.x << ", " << planetMeta.initialPosition.y << ")" << std::endl;
      std::cout << "\t\t -> Initial Velocity Vector: " << "(" << planetMeta.initialVelocity.x << ", " << planetMeta.initialVelocity.y << ")" << std::endl;

      celestialBody.setName(planetMeta.name)
        .setMass(planetMeta.mass)
        .setRadius(entities::CelestialBody::massToRadius(planetMeta.mass))
        .setPosition(planetMeta.initialPosition)
        .setVelocity(planetMeta.initialVelocity)
        .setColor(planetMeta.color)
        .build();
      celestialBodyRegistry[celestialBody.getName()] = celestialBody;
      std::cout << "\t => Done: " << planetMeta.name << " is created successfully" << std::endl;
    };

    for(const auto &pair: celestialBodyRegistry){
      celestialBodies.push_back(pair.second);
    }

    std::cout << "DONE: Planets are initialised successfully" << std::endl;
  }

  void App::drawCelestialBody(entities::CelestialBody celestialBody){
    sf::CircleShape circle;
    circle.setRadius(celestialBody.getRadius());
    circle.setPosition(celestialBody.getPosition());
    circle.setFillColor(celestialBody.getColor());
    this->window.draw(circle);
  }

  void App::drawCelestialBodyPaths(entities::CelestialBody celestialBody){
    this->window.draw(celestialBody.getPathVertices(), celestialBody.getPaths().size(), sf::PrimitiveType::Lines);
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
      float gridPositionX = 10.0f + (275.0f*(index%constants::MAX_STATISTIC_COLUMNS));
      float gridPositionY = (j*20.0f) + 10.0f + 100*(index/constants::MAX_STATISTIC_COLUMNS);
      sf::Text text(this->font);
      text.setString(infos[j]);
      text.setFillColor(sf::Color::Cyan);
      text.setCharacterSize(14);
      text.setPosition({gridPositionX, gridPositionY});
      this->window.draw(text);
    }
  }
} 