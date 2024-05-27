#pragma once


#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>

class Physics
{
  sf::Vector2f velocity;
  sf::Vector2f tractionForce;
  sf::Vector2f dragForce;
  sf::Vector2f rollingForce;
  float speed;
  float acceleration;
  float steeringAngle;
  int sign;

public:
  Physics();
  ~Physics();

  void setTractionForce(int power);
  void setDragForce();
  void setRollingForce();
  void setAcceleration(float acceleration, int power, float angleInRad);
  void setSteeringAngle(float angle);
  void setSpeed(float speed);
  void setVelocity(float angleInRad);


  
  float getSpeed();
  float getAcceleration();
  float getSteeringAngle();

  int getSign();
};