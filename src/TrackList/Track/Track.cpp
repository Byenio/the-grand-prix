#include "Track.hpp"

Track::Track(const int id, const std::string name) : id(id), name(name){};

Track::~Track(){};

int Track::getId() const
{
  return this->id;
}

std::string Track::getName() const
{
  return this->name;
}