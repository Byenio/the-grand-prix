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
<<<<<<< Updated upstream
  this->speed = 0;
=======
  return 0.5 * d * v * v * liftCoeff * area;
}

sf::Vector2f calcDragForce(float d, float v, float dragCoeff, float area, float rotation, int speedSign)
{
  double x = (speedSign * 0.5 * d * v * v * dragCoeff * area) * sin(rotation);
  double y = (speedSign * 0.5 * d * v * v * dragCoeff * area) * -cos(rotation);
  return sf::Vector2f(x * cos(rotation) - y * sin(rotation) ,
                      x * sin(rotation) + y * cos(rotation));
}

sf::Vector2f calcTractionForce(float frictionCoeff, float normalForce, float rotation, int speedSign)
{
  double x = (speedSign * frictionCoeff * normalForce) * sin(rotation);
  double y = (speedSign * frictionCoeff * normalForce) * -cos(rotation);
  return sf::Vector2f(x * cos(rotation) - y * sin(rotation),
                      x * sin(rotation) + y * cos(rotation));
}

sf::Vector2f calcRollingForce(float rollingCoeff, float normalForce, float rotation, int speedSign)
{
  double x = (speedSign * rollingCoeff * normalForce) * sin(rotation);
  double y = (speedSign * rollingCoeff * normalForce) * -cos(rotation);
  return sf::Vector2f(x * cos(rotation) - y * sin(rotation),
                      x * sin(rotation) + y * cos(rotation));
}

sf::Vector2f calcBrakeForce(float brakeCoeff, float normalForce, float rotation, int speedSign)
{
  double x = (speedSign * brakeCoeff * normalForce) * sin(rotation);
  double y = (speedSign * brakeCoeff * normalForce) * -cos(rotation);
  return sf::Vector2f(x * cos(rotation) - y * sin(rotation),
                      x * sin(rotation) + y * cos(rotation));
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
    double x = (speedSign * ((power * throttlePower) / this->speed)) * sin(rotation);
    double y = (speedSign * ((power * throttlePower) / this->speed)) * -cos(rotation);
    propulsionForce = sf::Vector2f(x * cos(rotation) - y * sin(rotation),
                                  x * sin(rotation) + y * cos(rotation));
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

float Physics::turnAngle(float mass, float liftCoeff, float frontalArea, float frictionCoeff){
  float liftForce = calculateLiftForce(AIR_DENSITY, this->speed, liftCoeff, frontalArea);
  float normalForce = calculateNormalForce(mass, GRAVITY_ACCELERATION, liftForce);

  float minRadius = (mass*this->speed * this->speed) / (frictionCoeff * normalForce);

  float angularSpeed = this->speed / minRadius * 57.2957795 * TICKRATE_DELTA;

  return angularSpeed;
}

sf::Vector2f Physics::getAcceleration()
{
  return this->acceleration;
}

sf::Vector2f Physics::getVelocity()
{
  return this->velocity;
>>>>>>> Stashed changes
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