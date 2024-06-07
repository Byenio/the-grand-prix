#pragma once

#include "../CarList/Car/Car.hpp"
#include "../TrackList/Track/Track.hpp"
#include "../utils/json.hpp"
#include <fstream>
#include <iostream>
#include <memory>

using json = nlohmann::json;

class Session
{
  int id;
  std::shared_ptr<Track> track;
  std::shared_ptr<Car> car;
  sf::Clock clock;

public:
  Session(int id, std::shared_ptr<Track> track, std::shared_ptr<Car> car);
  ~Session();

  int getId();
  std::shared_ptr<Track> getTrack();
  std::shared_ptr<Car> getCar();
  sf::Clock getClock();

  json getTrackModel();
};