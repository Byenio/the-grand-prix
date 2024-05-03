#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "../CarList/CarList.hpp"
#include "../TrackList/TrackList.hpp"

class Game
{
  sf::RenderWindow *pWindow;
  std::shared_ptr<TrackList> pTrackList;
  std::shared_ptr<CarList> pCarList;

public:
  Game(sf::RenderWindow *pWindow);
  ~Game();

  std::shared_ptr<Track> selectTrack(int id);

  void close();
};