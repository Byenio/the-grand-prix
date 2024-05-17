#include "Physics.hpp"

Physics::Physics() : speed(0), acceleration(0), steeringAngle(0), sign(1)
{
}

Physics::~Physics(){};

void Physics::setSpeed(float speed)
{
  this->speed = speed;
}

float Physics::getSpeed()
{
  return this->speed;
}

void Physics::setAcceleration(float acceleration)
{
  float accelerationCoefficient = 0.0001;
  this->acceleration = acceleration;
  this->speed += accelerationCoefficient * acceleration;
  speed >= 0 ? this->sign = 1 : this->sign = -1;
};

float Physics::getAcceleration()
{
  return this->acceleration;
}

void Physics::setSteeringAngle(float angle)
{
  this->steeringAngle = angle * sign;
}

float Physics::getSteeringAngle()
{
  return this->steeringAngle;
}

int Physics::getSign()
{
  return this->sign;
}