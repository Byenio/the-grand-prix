#pragma once

#include "Player/Player.hpp"
#include "Racetrack.hpp"
#include <iostream>

class Lap
{
  static int sID;
  int id;
  Player *pPlayer;
  Racetrack *pRacetrack;
  int timeMs;

public:
  Lap(Player *pPlayer, Racetrack *pRacetrack, int timeMs);
  virtual ~Lap();

  int getTime();
  int getId();
};