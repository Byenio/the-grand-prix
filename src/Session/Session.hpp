#pragma once

#include "../CarList/Car/Car.hpp"
#include "../TrackList/Track/Track.hpp"
#include <iostream>
#include <memory>

class Session
{
  int id;
  std::shared_ptr<Track> track;
  std::shared_ptr<Car> car;

public:
  Session(int id, std::shared_ptr<Track> track, std::shared_ptr<Car> car);
  ~Session();

  int getId();
  std::shared_ptr<Track> getTrack();
  std::shared_ptr<Car> getCar();
};