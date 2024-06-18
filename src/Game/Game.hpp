#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "../CarList/CarList.hpp"
#include "../Session/Session.hpp"
#include "../TrackList/TrackList.hpp"

class Game
{
  sf::RenderWindow *pWindow;
  std::unique_ptr<TrackList> pTracks;
  std::unique_ptr<CarList> pCars;
  std::shared_ptr<Session> pSession;

public:
  Game(sf::RenderWindow *pWindow);
  ~Game();

  void startSession(int trackId, int carId);
  std::shared_ptr<Session> getSession();
  std::shared_ptr<Car> getCar();
};