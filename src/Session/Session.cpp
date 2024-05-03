#include "Session.hpp"

Session::Session(Player *pPlayer, Racetrack *pRacetrack) : id(sID++), pPlayer(pPlayer), pRacetrack(pRacetrack)
{
  std::cout << "Successfully created session: " << id << " " << pPlayer->getId() << " " << pRacetrack->getId() << " "
            << std::endl;
}

Session::~Session(){};

void Session::pushLap(Lap *pLap)
{
  laps.push_back(pLap);
  std::cout << "Successfully pushed new lap to session array" << std::endl;
}

bool compareLaptime(Lap *pLap1, Lap *pLap2)
{
  return pLap1->getTime() < pLap2->getTime();
}

int Session::fastestLap()
{
  if (laps.size() <= 0)
    return -1;

  std::sort(laps.begin(), laps.end(), compareLaptime);

  return laps.at(0)->getId();
}

int Session::getId()
{
  return this->id;
}

std::string Session::getRacetrackName()
{
  return this->pRacetrack->getName();
}

int Session::sID = 0;