#include "Physics.hpp"

Physics::Physics() : speed(0), acceleration(0), steeringAngle(0), speedSign(1)
{
}

Physics::~Physics(){};

void Physics::setSpeed()
{
  std::cout<<velocityX<<" "<<velocityY<<" "<<std::endl;
  this->speed = sqrt(this->velocityX * this->velocityX + this->velocityY * this->velocityY);
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
  if (this->speed == 0){
    this->tractionForce = 0;
  } 
  else{
    this->tractionForce = (0.9*power) / speed;
  } 
}

void Physics::setDragForce()
{
  this->dragForce = 0.5 * 1.29 * 0.7 * 1.5 * speed * speed;
}

void Physics::setRollingForce()
{
  if(this->speed == 0){
    this->rollingForce = 0;
  }else{
    this->rollingForce = 0.015 * normalForce; 
  }
}

void Physics::setNormalForce(){
  this->normalForce = 900 * 9.81 + 15000;
}

void Physics::setAcceleration(int power, float angleInRad)
{
  setVelocity();
  setSpeed();
  setTractionForce(power);
  setDragForce();
  setNormalForce();
  setRollingForce();
  this->acceleration = (tractionForce - dragForce - rollingForce)/900;
  //std::cout << acceleration << std::endl;
  //std::cout << tractionForce << std::endl;
  //std::cout << rollingForce << std::endl;
  std::cout << dragForce << std::endl;
  //std::cout << angleInRad << std::endl;

  this->accelerationX = acceleration * cos(angleInRad);
  this->accelerationY = acceleration * sin(angleInRad);

  

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