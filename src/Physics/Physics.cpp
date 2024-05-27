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

void Physics::setVelocity(float angleInRad){
  this->velocity =sf::Vector2f(sin(angleInRad)*speed, -cos(angleInRad)*speed);
}


void Physics::setTractionForce(int power){
  this->tractionForce = sf::Vector2f(
    0.7*power,
    0.7*power);
}

void Physics::setDragForce(){
  this->dragForce = sf::Vector2f(
    -0.4257*speed*velocity.x,
    -0.4257*speed*velocity.y);
}

void Physics::setRollingForce(){
  this->rollingForce = sf::Vector2f(
    -0.4257*30*velocity.x,
    -0.4257*30*velocity.y
  );
}

void Physics::setAcceleration(float acceleration, int power, float angleInRad)
{
  setVelocity(angleInRad);
  setTractionForce(power);
  setDragForce();
  setRollingForce();
  sf::Vector2f forces = (tractionForce+rollingForce+dragForce);
  sf::Vector2f accelerationVector = sf::Vector2f(forces.x/900,forces.y/900);
  this->acceleration = sqrt(accelerationVector.x*accelerationVector.x+accelerationVector.y*accelerationVector.y);
  this->speed += acceleration;
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