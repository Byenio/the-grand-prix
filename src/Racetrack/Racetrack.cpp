#include "Racetrack.hpp"

Racetrack::Racetrack(std::string name) : id(sID++), name(name)
{
  std::cout << "Successfully created racetrack: " << name << std::endl;
}

Racetrack::~Racetrack(){};

int Racetrack::getId()
{
  return this->id;
}

std::string Racetrack::getName()
{
  return this->name;
}

int Racetrack::sID = 0;