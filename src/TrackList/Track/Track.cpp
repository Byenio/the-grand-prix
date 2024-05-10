#include "Track.hpp"

Track::Track(const int id, const std::string name)
    : id(id), name(name){
                  // std::cout << "Successfully created new track: [" << id << "] " <<
                  // name << std::endl;
              };

Track::~Track(){};

int Track::getId() const
{
  return this->id;
}

std::string Track::getName() const
{
  return this->name;
}