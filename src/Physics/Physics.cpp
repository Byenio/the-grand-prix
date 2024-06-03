#include "Physics.hpp"

Physics::Physics() : speed(0), acceleration(0), steeringAngle(0), speedSign(1)
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

sf::Vector2f Physics::getVelocity()
{
  return this->velocity;
}

void Physics::setVelocity(float angleInRad)
{
  this->velocity = sf::Vector2f(sin(angleInRad) * speed, -cos(angleInRad) * speed);
}

void Physics::setTractionForce(int power, float angleInRad)
{
  this->tractionForce = sf::Vector2f(0.7 * power * sin(angleInRad), 0.7 * power * (-cos(angleInRad)));
}

void Physics::setDragForce()
{
  this->dragForce = sf::Vector2f(-1.29 * speed * velocity.x, -1.29 * speed * velocity.y);
}

void Physics::setRollingForce()
{
  this->rollingForce = sf::Vector2f(-1.29 * 30 * speed, -1.29 * 30 * speed);
}

void Physics::setAcceleration(int power, float angleInRad)
{
  setVelocity(angleInRad);
  setTractionForce(power, angleInRad);
  setDragForce();
  setRollingForce();

  sf::Vector2f accelerationVector = sf::Vector2f(tractionForce.x / 900, tractionForce.y / 900);
  sf::Vector2f decelerationVector =
      sf::Vector2f((rollingForce.x + dragForce.x) / 900, (rollingForce.y + dragForce.y) / 900);

  this->acceleration = 
  sqrt(accelerationVector.x * accelerationVector.x + accelerationVector.y * accelerationVector.y) - 
  sqrt(decelerationVector.x * decelerationVector.x + decelerationVector.y * decelerationVector.y);

  this->speed += this->acceleration*1.0f/30.0f;

  speed >= 0 ? this->speedSign = 1 : this->speedSign = -1;
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