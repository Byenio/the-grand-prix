#pragma once

class Physics
{
  float speed;
  float acceleration;
  float steeringAngle;
  int sign;

public:
  Physics();
  ~Physics();

  void setAcceleration(float acceleration);
  void setSteeringAngle(float angle);

  void setSpeed(float speed);

  float getSpeed();
  float getAcceleration();
  float getSteeringAngle();

  int getSign();
};