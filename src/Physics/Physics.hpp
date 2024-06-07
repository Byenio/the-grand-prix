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

  float acceleration;
  float speed;

public:
  Physics();
  ~Physics();

  void accelerate(float power, float mass, float dragCoeff, float liftCoeff, float frontalArea, float rollingCoeff,
                  float frictionCoeff);

  void decelerate();

  float getAcceleration();
  float getSpeed();
};