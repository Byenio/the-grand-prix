#include "Menu.hpp"

Menu::Menu()
{
  font.loadFromFile("src/assets/fonts/JetBrainsMono.ttf");
  // Play
  menu[0].setFont(font);
  menu[0].setString("Play");
  menu[0].setFillColor(sf::Color::White);
  menu[0].setCharacterSize(70);
  menu[0].setPosition(400, 200);
  // Leaderboards
  menu[1].setFont(font);
  menu[1].setString("Leaderboards");
  menu[1].setFillColor(sf::Color::White);
  menu[1].setCharacterSize(70);
  menu[1].setPosition(400, 300);
  // Exit
  menu[2].setFont(font);
  menu[2].setString("Exit");
  menu[2].setFillColor(sf::Color::White);
  menu[2].setCharacterSize(70);
  menu[2].setPosition(400, 400);

  menuSelected = 0;
}

Menu::~Menu(){};

void Menu::draw(sf::RenderWindow *window)
{
  for (int i = 0; i < 3; i++)
  {
    window->draw(menu[i]);
    menu[menuSelected].setFillColor(sf::Color::Blue);
  }
}

void Menu::moveUp()
{
  if (menuSelected >= 0)
  {
    menu[menuSelected].setFillColor(sf::Color::White);

    menuSelected--;
    if (menuSelected == -1)
    {
      menuSelected = 2;
    }
    menu[menuSelected].setFillColor(sf::Color::Blue);
  }
}

void Menu::moveDown()
{
  if (menuSelected <= 3)
  {
    menu[menuSelected].setFillColor(sf::Color::White);
    menuSelected++;
    if (menuSelected == 3)
    {
      menuSelected = 0;
    }
    menu[menuSelected].setFillColor(sf::Color::Blue);
  }
}