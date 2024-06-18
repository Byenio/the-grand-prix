#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

class Setup
{
  std::vector<sf::Text> tracks;
  std::vector<sf::Text> cars;
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