#include "Physics.hpp"

Physics::Physics() : acceleration(0), speed(0){};

Physics::~Physics(){};

float calcNormalForce(float mass, float g, float liftForce)
{
  return mass * g - liftForce;
}

float calculateDownforce(float d, float v, float liftCoeff, float area)
{
  return 0.5 * d * v * v * liftCoeff * area;
}

float calculateDragForce(float d, float v, float dragCoeff, float area)
{
  return 0.5 * d * v * v * dragCoeff * area;
}

float calculateTractionForce(float frictionCoeff, float normalForce)
{
  return frictionCoeff * normalForce;
}

float calculateRollingResistanceForce(float rollingCoeff, float normalForce)
{
  return rollingCoeff * normalForce;
}

float throttleMap(float speed)
{
  float throttlePower;
  if (speed <= 28.0f)
  {
    float base = 1.1f;
    throttlePower = (std::exp(speed / (28.0f) * std::log(base)) - 1.0f) / (base - 1.0f);
  }
  else
  {
    throttlePower = 1.0f;
  }
  return throttlePower;
}

void Physics::accelerate(float power, float mass, float dragCoeff, float liftCoeff, float frontalArea,
                         float rollingCoeff, float frictionCoeff)
{
  float liftForce = calculateDownforce(AIR_DENSITY, this->speed, liftCoeff, frontalArea);
  float normalForce = calcNormalForce(mass, GRAVITY_ACCELERATION, liftForce);

  float tractionForce = calculateTractionForce(frictionCoeff, normalForce);
  float dragForce = calculateDragForce(AIR_DENSITY, this->speed, dragCoeff, frontalArea);
  float rollingResistanceForce = calculateRollingResistanceForce(rollingCoeff, normalForce);

  float throttlePower = throttleMap(this->speed);
  float engineForce;
  if (std::fabs(this->speed) > 1e-6f)
  {
    engineForce = (power * throttlePower) / this->speed;
  }
  else
  {
    engineForce = frictionCoeff * normalForce * 0.1f;
  }

  float netForce = engineForce - dragForce - rollingResistanceForce;

  this->acceleration = netForce / mass;

  this->speed += this->acceleration * TICKRATE_DELTA;
}

void decelerate()
{
}

float Physics::getAcceleration()
{
  return this->acceleration;
}

float Physics::getSpeed()
{
  return this->speed;
}