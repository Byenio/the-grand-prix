#pragma once

#include "../../Physics/Engine/Engine.hpp"
#include "../../Physics/Physics.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Car
{
  int id;
  std::string name;
  std::shared_ptr<sf::Texture> texture;
  std::shared_ptr<sf::Sprite> sprite;

  std::shared_ptr<Engine> engine;

  std::shared_ptr<Physics> physics;
  float acceleration = .2;
  float dragAcceleration = -.1;
  float brakeAcceleration = -2;
  float steeringAngle = .3;
  float reverseAcceleration = -.5;

public:
  Car(const int id, const std::string name, const std::string texturePath, const int horsepower);
  ~Car();

  int getId() const;
  std::string getName() const;
  std::shared_ptr<sf::Sprite> getSprite() const;

  std::shared_ptr<Engine> getEngine() const;

  std::shared_ptr<Physics> getPhysics() const;

  void accelerate();
  void decelerate();
  void brake();
  void reverse();
  void turnLeft();
  void turnRight();

  void update();
};