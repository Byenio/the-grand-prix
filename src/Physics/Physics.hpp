#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>

class Physics
{
  sf::Vector2f velocity;
  sf::Vector2f tractionForce;
  sf::Vector2f dragForce;
  sf::Vector2f rollingForce;
  float speed;
  float acceleration;
  float steeringAngle;
  int speedSign;

public:
  Physics();
  ~Physics();

  void setTractionForce(int power, float angleInRad);
  void setDragForce();
  void setRollingForce();
  void setAcceleration(int power, float angleInRad);
  void setSteeringAngle(float angle);
  void setSpeed(float speed);
  void setVelocity(float angleInRad);

  float getSpeed();
  float getAcceleration();
  float getSteeringAngle();
  sf::Vector2f getVelocity();

  int getSign();
};