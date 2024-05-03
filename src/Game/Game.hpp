#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Game
{
public:
  Game();
  ~Game();

  void close(sf::RenderWindow &rWindow);
};