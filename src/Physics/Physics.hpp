#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>

class Physics
{
  float tractionForce;
  float dragForce;
  float rollingForce;
  float normalForce;

  float speed;
  float velocityX;
  float velocityY;

  float acceleration;
  float accelerationX;
  float accelerationY;

  float steeringAngle;

  int speedSign;

public:
  Physics();
  ~Physics();

  void setTractionForce(int power);
  void setDragForce();
  void setRollingForce();
  void setNormalForce();
  void setAcceleration(int power, float angleInRad);
  void setNegativeAcceleration(int power, float angleInRad);
  void setSteeringAngle(float angle);
  void setSpeed();
  void setSpeed(float speed);
  void setVelocity();

  float getSpeed();
  float getAcceleration();
  float getSteeringAngle();
  sf::Vector2f getVelocity();

  int getSign();
};