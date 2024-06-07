#include "Physics.hpp"

Physics::Physics()
    : speed(0), velocityX(0), velocityY(0), acceleration(0), accelerationX(0), accelerationY(0), steeringAngle(0),
      speedSign(1)
{
}

Physics::~Physics(){};

void Physics::setSpeed()
{
  this->speed = sqrt(this->velocityX * this->velocityX + this->velocityY * this->velocityY);
}

void Physics::setSpeed(float speed)
{
  this->speed = 0;
}

float Physics::getSpeed()
{
  return this->speed;
}

sf::Vector2f Physics::getVelocity()
{
  return sf::Vector2f(velocityX, velocityY);
}

void Physics::setVelocity()
{
  this->velocityX += accelerationX;
  this->velocityY += accelerationY;
}

void Physics::setTractionForce(int power)
{
  if (this->speed == 0)
  {
    this->tractionForce = abs((0.9 * power));
  }
  else
  {
    this->tractionForce = abs((0.9 * power) / speed);
  }
}

void Physics::setDragForce()
{
  this->dragForce = 0.5 * 1.29 * 0.7 * 1.5 * speed * speed;
}

void Physics::setRollingForce()
{
  {
    this->rollingForce = 0.015 * normalForce;
  }
}

void Physics::setNormalForce()
{
  this->normalForce = 900 * 9.81 + 15000;
}

void Physics::setAcceleration(int power, float angleInRad)
{
  setTractionForce(power);
  setDragForce();
  setNormalForce();
  setRollingForce();
  this->acceleration = (tractionForce - dragForce - rollingForce) / 900;
  std::cout << "a " << acceleration << std::endl;
  std::cout << "t " << tractionForce << std::endl;
  std::cout << "r " << rollingForce << std::endl;
  std::cout << "d " << dragForce << std::endl;

  this->accelerationX = acceleration * sin(angleInRad);
  this->accelerationY = acceleration * -cos(angleInRad);

  speed >= 0 ? this->speedSign = 1 : this->speedSign = -1;

  setVelocity();
  setSpeed();
};

void Physics::setNegativeAcceleration(int power, float angleInRad)
{
  setTractionForce(power);
  setDragForce();
  setNormalForce();
  setRollingForce();
  this->acceleration = (tractionForce - rollingForce) / 900;
  std::cout << "a " << acceleration << std::endl;
  std::cout << "t " << tractionForce << std::endl;
  std::cout << "r " << rollingForce << std::endl;
  std::cout << "d " << dragForce << std::endl;

  this->accelerationX = acceleration * sin(angleInRad);
  this->accelerationY = acceleration * -cos(angleInRad);

  speed >= 0 ? this->speedSign = 1 : this->speedSign = -1;

  setVelocity();
  setSpeed();
};

float Physics::getAcceleration()
{
  return this->acceleration;
}

void Physics::setSteeringAngle(float angle)
{
  this->steeringAngle = angle * speedSign;
}

float Physics::getSteeringAngle()
{
  return this->steeringAngle;
}

int Physics::getSign()
{
  return this->speedSign;
}