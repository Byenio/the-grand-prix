#include "Session.hpp"

Session::Session(int id, std::shared_ptr<Track> track, std::shared_ptr<Car> car)
    : id(id), track(track), car(car), clock(){};

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

sf::Clock Session::getClock()
{
  return this->clock;
}

json Session::getTrackModel()
{

  std::string fileName = "src/config/tracks/" + std::to_string(track->getId()) + "/track_model.json";

  std::fstream file;
  file.open(fileName, std::ios::in);
  json trackModel{json::parse(file)};

  return trackModel;
}