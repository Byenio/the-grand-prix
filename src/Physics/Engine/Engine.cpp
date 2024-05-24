#include "Engine.hpp"

Engine::Engine(int power) : power(power){};

Engine::~Engine(){};

int Engine::getPower()
{
  return this->power;
}