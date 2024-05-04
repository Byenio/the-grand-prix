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
  std::shared_ptr<TrackList> pTracks;
  std::shared_ptr<CarList> pCars;
  Session *pSession;

public:
  Game(sf::RenderWindow *pWindow);
  ~Game();

  void startSession(int trackId, int carId);
  void closeSession();

  void closeGame();
};