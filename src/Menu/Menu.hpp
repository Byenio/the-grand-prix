#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
  int menuSelected;
  sf::Text menu[3];
  sf::Font font;

public:
  Menu();

  void draw(sf::RenderWindow *window);
  void moveUp();
  void moveDown();

  int menuPressed()
  {
    return menuSelected;
  }
  ~Menu();
};