#include "Physics.hpp"

Physics::Physics() : acceleration(0, 0), velocity(0, 0), speed(0), speedSign(1){};

Physics::~Physics(){};

float calculateNormalForce(float mass, float g, float liftForce)
{
  return mass * g - liftForce;
}

float calculateLiftForce(float d, float v, float liftCoeff, float area)
{
  return 0.5 * d * v * v * liftCoeff * area;
}

sf::Vector2f calcDragForce(float d, float v, float dragCoeff, float area, float rotation, int speedSign)
{
  return sf::Vector2f(speedSign * 0.5 * d * v * v * dragCoeff * area * sin(rotation),
                      speedSign * 0.5 * d * v * v * dragCoeff * area * -cos(rotation));
}

sf::Vector2f calcTractionForce(float frictionCoeff, float normalForce, float rotation, int speedSign)
{
  return sf::Vector2f(speedSign * frictionCoeff * normalForce * sin(rotation),
                      speedSign * frictionCoeff * normalForce * -cos(rotation));
}

sf::Vector2f calcRollingForce(float rollingCoeff, float normalForce, float rotation, int speedSign)
{
  return sf::Vector2f(speedSign * rollingCoeff * normalForce * sin(rotation),
                      speedSign * rollingCoeff * normalForce * -cos(rotation));
}

sf::Vector2f calcBrakeForce(float brakeCoeff, float normalForce, float rotation, int speedSign)
{
  return sf::Vector2f(speedSign * brakeCoeff * normalForce * sin(rotation),
                      speedSign * brakeCoeff * normalForce * -cos(rotation));
}

float throttleMap(float speed, float speedSign)
{
  float throttlePower;

  if (speedSign == 1)
  {
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

  if (speedSign * speed <= 8.0f)
  {
    float base = 0.1f;
    throttlePower = (std::exp(speedSign * speed / (8.0f) * std::log(base)) - 1.0f) / (base - 1.0f);
  }
  else
  {
    throttlePower = 1.0f;
  }
  return speedSign * throttlePower;
}

void Physics::accelerate(float power, float mass, float dragCoeff, float liftCoeff, float frontalArea,
                         float rollingCoeff, float frictionCoeff, float rotation)
{
  float liftForce = calculateLiftForce(AIR_DENSITY, this->speed, liftCoeff, frontalArea);
  float normalForce = calculateNormalForce(mass, GRAVITY_ACCELERATION, liftForce);

  sf::Vector2f tractionForce = calcTractionForce(frictionCoeff, normalForce, rotation, speedSign);
  sf::Vector2f dragForce = calcDragForce(AIR_DENSITY, this->speed, dragCoeff, frontalArea, rotation, speedSign);
  sf::Vector2f rollingForce = calcRollingForce(rollingCoeff, normalForce, rotation, speedSign);

  float throttlePower = throttleMap(this->speed, this->speedSign);
  sf::Vector2f propulsionForce;
  if (std::fabs(this->speed) > 1e-6f)
  {
    propulsionForce = sf::Vector2f(speedSign * ((power * throttlePower) / this->speed * sin(rotation)),
                                   speedSign * ((power * throttlePower) / this->speed * -cos(rotation)));
  }
  else
  {
    propulsionForce = tractionForce * 0.1f;
  }

  sf::Vector2f netForce = propulsionForce - dragForce - rollingForce;
  this->acceleration = netForce / mass;
  this->velocity += this->acceleration * TICKRATE_DELTA;
  this->speed = this->speedSign * sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);
}

void Physics::decelerate(float mass, float dragCoeff, float liftCoeff, float frontalArea, float rollingCoeff,
                         float frictionCoeff, float rotation)
{
  float liftForce = calculateLiftForce(AIR_DENSITY, this->speed, liftCoeff, frontalArea);
  float normalForce = calculateNormalForce(mass, GRAVITY_ACCELERATION, liftForce);

  sf::Vector2f dragForce = calcDragForce(AIR_DENSITY, this->speed, dragCoeff, frontalArea, rotation, speedSign);
  sf::Vector2f rollingResistanceForce = calcRollingForce(rollingCoeff, normalForce, rotation, speedSign);

  sf::Vector2f netForce = -dragForce - rollingResistanceForce;
  this->acceleration = netForce / mass;
  this->velocity += this->acceleration * TICKRATE_DELTA;
  this->speed = this->speedSign * sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);
}

void Physics::brake(float mass, float dragCoeff, float liftCoeff, float frontalArea, float rollingCoeff,
                    float frictionCoeff, float brakeCoeff, float rotation)
{
  float liftForce = calculateLiftForce(AIR_DENSITY, this->speed, liftCoeff, frontalArea);
  float normalForce = calculateNormalForce(mass, GRAVITY_ACCELERATION, liftForce);

  sf::Vector2f brakeForce = calcBrakeForce(brakeCoeff, normalForce, rotation, speedSign);
  sf::Vector2f dragForce = calcDragForce(AIR_DENSITY, this->speed, dragCoeff, frontalArea, rotation, speedSign);
  sf::Vector2f rollingForce = calcRollingForce(rollingCoeff, normalForce, rotation, speedSign);

  sf::Vector2f netForce = -brakeForce - dragForce - rollingForce;
  this->acceleration = netForce / mass;

  sf::Vector2f resVelocity = this->velocity + this->acceleration * TICKRATE_DELTA;
  float resSpeed = sqrt(resVelocity.x * resVelocity.x + resVelocity.y * resVelocity.y);

  const float speedThreshold = 1.0f;
  if (resSpeed < speedThreshold)
  {
    this->velocity = sf::Vector2f(0, 0);
    this->speed = 0;
    this->acceleration = sf::Vector2f(0, 0);
  }
  else
  {
    this->velocity = resVelocity;
    this->speed = this->speedSign * resSpeed;
  }
}

sf::Vector2f Physics::getAcceleration()
{
  return this->acceleration;
}

sf::Vector2f Physics::getVelocity()
{
  return this->velocity;
}

float Physics::getSpeed()
{
  return this->speed;
}

void Physics::setNegativeSpeedSign()
{
  this->speedSign = -1;
}

void Physics::setPositiveSpeedSign()
{
  this->speedSign = 1;
}

int Physics::getSpeedSign()
{
  return this->speedSign;
}