#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>

class Physics
{
  const float AIR_DENSITY = 1.29f;
  const float GRAVITY_ACCELERATION = 9.81f;
  const float TICKRATE_DELTA = 1.0f / 32.0f;

  sf::Vector2f acceleration;
  sf::Vector2f velocity;
  float speed;

  int speedSign;

public:
  Physics();
  ~Physics();

  void accelerate(float power, float mass, float dragCoeff, float liftCoeff, float frontalArea, float rollingCoeff,
                  float frictionCoeff, float rotation);

  void decelerate(float mass, float dragCoeff, float liftCoeff, float frontalArea, float rollingCoeff,
                  float frictionCoeff, float rotation);

  void brake(float mass, float dragCoeff, float liftCoeff, float frontalArea, float rollingCoeff, float frictionCoeff,
             float brakeCoeff, float rotation);

  float turnAngle(float mass, float liftCoeff, float frontalArea, float frictionCoeff, int direction);

  sf::Vector2f getAcceleration();
  sf::Vector2f getVelocity();
  float getSpeed();

  void setNegativeSpeedSign();
  void setPositiveSpeedSign();
  int getSpeedSign();
};