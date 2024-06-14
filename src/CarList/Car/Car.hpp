#pragma once

#include "../../Physics/Engine/Engine.hpp"
#include "../../Physics/Physics.hpp"
#include "../../Physics/Tyre/Tyre.hpp"
#include "../../utils/functions.hpp"
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
  std::vector<std::shared_ptr<Tyre>> tyres;

  std::shared_ptr<Physics> physics;

  float rotation = 0;

  const float MASS = 900.0f;

  const float DRAG_COEFF = 0.8f;
  const float LIFT_COEFF = -3.0f;
  const float FRONTAL_AREA = 1.4f;

  const float ROLL_COEFF = 0.015f;
  float ROLL_COEFF_MULTIPLIER = 1.0f;
  const float FRICTION_COEFF = 1.5f;

  const float BRAKE_COEFF = 1.2f;

  const float DEG_TO_RAD = M_PI / 180.0f;
  const float RAD_TO_DEG = 180.0f / M_PI;

public:
  Car(const int id, const std::string name, const std::string texturePath, const int horsepower, const float grip);
  ~Car();

  int getId() const;
  std::string getName() const;
  std::shared_ptr<sf::Sprite> getSprite() const;

  std::shared_ptr<Engine> getEngine() const;
  std::vector<std::shared_ptr<Tyre>> getTyres() const;

  std::shared_ptr<Physics> getPhysics() const;

  void accelerate();
  void decelerate();
  void brake();
  void reverse();
  void turnLeft();
  void turnRight();

  void update();

  float getRotation();
  void setRotation(float angle);

  void multiplyRollCoeff(float multiplier);
};