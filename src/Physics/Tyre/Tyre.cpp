#include "Tyre.hpp"
#include <iostream>

Tyre::Tyre(int width, float grip) : width(width), grip(grip){};

Tyre::~Tyre(){};

int Tyre::getWidth()
{
  return this->width;
}

float Tyre::getGrip()
{
  return this->grip;
}