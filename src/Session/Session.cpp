#include "Session.hpp"

Session::Session(int id, std::shared_ptr<Track> track, std::shared_ptr<Car> car) : id(id), track(track), car(car){};

Session::~Session(){};

int Session::getId()
{
  return this->id;
}

std::shared_ptr<Track> Session::getTrack()
{
  return this->track;
}

std::shared_ptr<Car> Session::getCar()
{
  return this->car;
}