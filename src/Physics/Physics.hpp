#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>

class Physics
{
  float velocityX;
  float velocityY;
  float tractionForce;
  float dragForce;
  float rollingForce;
  float normalForce;
  float speed;
  float accelerationX = 0;
  float accelerationY = 0;
  float acceleration;
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
  void setSteeringAngle(float angle);
  void setSpeed();
  void setVelocity();

  float getSpeed();
  float getAcceleration();
  float getSteeringAngle();
  sf::Vector2f getVelocity();

  int getSign();
};