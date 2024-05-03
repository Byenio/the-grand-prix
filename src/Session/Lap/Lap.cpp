#include "Lap.hpp"

Lap::Lap(Player *pPlayer, Racetrack *pRacetrack, int timeMs)
    : id(sID++), pPlayer(pPlayer), pRacetrack(pRacetrack), timeMs(timeMs)
{
  std::cout << "Successfully recorded a lap: " << id << " " << pPlayer->getId() << " " << pRacetrack->getId() << " "
            << timeMs << std::endl;
};

Lap::~Lap(){};

int Lap::getTime()
{
  return this->timeMs;
};

int Lap::getId()
{
  return this->id;
};

int Lap::sID = 0;