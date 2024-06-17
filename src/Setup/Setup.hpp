#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Setup
{
  sf::Text tracks[11];
  sf::Text cars[10];
  sf::Font font;

  int selectedTrack;
  int selectedCar;

public:
  Setup();
  void draw(sf::RenderWindow *window);
  ~Setup();

  int getSelectedTrack();
  int getSelectedCar();

  void moveUpTrack();
  void moveDownTrack();

  void moveUpCar();
  void moveDownCar();
};
