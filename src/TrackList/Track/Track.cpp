#include "Track.hpp"

Track::Track(int id, std::string name) : id(id), name(name)
{
  std::cout << "Successfully created new track: [" << id << "] " << name << std::endl;
};

Track::~Track(){};

int Track::getId()
{
  return this->id;
}

std::string Track::getName()
{
  return this->name;
}