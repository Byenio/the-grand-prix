#include "Menu.hpp"

Menu::Menu()
{
  font.loadFromFile("assets/fonts/JetBrainsMono.ttf");

  std::string menuStrings[] = {"Play", "Leaderboards", "Exit"};

  int windowWidth = 1600;

  for (int i = 0; i < 3; ++i)
  {
    menu[i].setFont(font);
    menu[i].setString(menuStrings[i]);
    menu[i].setFillColor(sf::Color::Black);
    menu[i].setCharacterSize(70);
  }

  for (int i = 0; i < 3; ++i)
  {
    sf::FloatRect textRect = menu[i].getLocalBounds();
    menu[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    menu[i].setPosition(windowWidth / 2.0f, 350 + i * 100);
  }

  menuSelected = 0;
}

Menu::~Menu(){};

void Menu::draw(sf::RenderWindow *window)
{
  for (int i = 0; i < 3; i++)
  {
    window->draw(menu[i]);
    menu[menuSelected].setFillColor(sf::Color::Red);
  }
}

void Menu::moveUp()
{
  if (menuSelected >= 0)
  {
    menu[menuSelected].setFillColor(sf::Color::Black);

    menuSelected--;
    if (menuSelected == -1)
    {
      menuSelected = 2;
    }
    menu[menuSelected].setFillColor(sf::Color::Red);
  }
}

void Menu::moveDown()
{
  if (menuSelected <= 3)
  {
    menu[menuSelected].setFillColor(sf::Color::Black);
    menuSelected++;
    if (menuSelected == 3)
    {
      menuSelected = 0;
    }
    menu[menuSelected].setFillColor(sf::Color::Red);
  }
}