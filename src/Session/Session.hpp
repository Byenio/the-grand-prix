#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include "Lap/Lap.hpp"
#include "Player/Player.hpp"
#include "Racetrack.hpp"

class Session
{
  static int sID;
  int id;
  Player *pPlayer;
  Racetrack *pRacetrack;
  std::vector<Lap *> laps;

public:
  Session(Player *pPlayer, Racetrack *pRacetrack);
  virtual ~Session();

  void pushLap(Lap *pLap);

  int fastestLap();
  int getId();
  std::string getRacetrackName();
};