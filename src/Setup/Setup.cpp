#include "Setup.hpp"

Setup::Setup()
{
  font.loadFromFile("assets/fonts/JetBrainsMono.ttf");

  tracks[0].setFont(font);
  tracks[0].setString("Japan");
  tracks[0].setFillColor(sf::Color::White);
  tracks[0].setCharacterSize(16);
  tracks[0].setPosition(200, 200);

  tracks[1].setFont(font);
  tracks[1].setString("Canada");
  tracks[1].setFillColor(sf::Color::White);
  tracks[1].setCharacterSize(16);
  tracks[1].setPosition(200, 250);

  tracks[2].setFont(font);
  tracks[2].setString("Spain");
  tracks[2].setFillColor(sf::Color::White);
  tracks[2].setCharacterSize(16);
  tracks[2].setPosition(200, 300);

  tracks[3].setFont(font);
  tracks[3].setString("Great Britain");
  tracks[3].setFillColor(sf::Color::White);
  tracks[3].setCharacterSize(16);
  tracks[3].setPosition(200, 350);

  tracks[4].setFont(font);
  tracks[4].setString("Hungary");
  tracks[4].setFillColor(sf::Color::White);
  tracks[4].setCharacterSize(16);
  tracks[4].setPosition(200, 400);

  tracks[5].setFont(font);
  tracks[5].setString("Belgium");
  tracks[5].setFillColor(sf::Color::White);
  tracks[5].setCharacterSize(16);
  tracks[5].setPosition(200, 450);

  tracks[6].setFont(font);
  tracks[6].setString("Italy");
  tracks[6].setFillColor(sf::Color::White);
  tracks[6].setCharacterSize(16);
  tracks[6].setPosition(200, 500);

  tracks[7].setFont(font);
  tracks[7].setString("Brazil");
  tracks[7].setFillColor(sf::Color::White);
  tracks[7].setCharacterSize(16);
  tracks[7].setPosition(200, 550);

  cars[0].setFont(font);
  cars[0].setString("RedBull");
  cars[0].setFillColor(sf::Color::White);
  cars[0].setCharacterSize(20);
  cars[0].setPosition(400, 200);

  cars[1].setFont(font);
  cars[1].setString("Ferrari");
  cars[1].setFillColor(sf::Color::White);
  cars[1].setCharacterSize(20);
  cars[1].setPosition(400, 250);

  cars[2].setFont(font);
  cars[2].setString("Mercedes");
  cars[2].setFillColor(sf::Color::White);
  cars[2].setCharacterSize(20);
  cars[2].setPosition(400, 300);

  cars[3].setFont(font);
  cars[3].setString("McLaren");
  cars[3].setFillColor(sf::Color::White);
  cars[3].setCharacterSize(20);
  cars[3].setPosition(400, 350);

  cars[4].setFont(font);
  cars[4].setString("AstonMartin");
  cars[4].setFillColor(sf::Color::White);
  cars[4].setCharacterSize(20);
  cars[4].setPosition(400, 400);

  cars[5].setFont(font);
  cars[5].setString("Williams");
  cars[5].setFillColor(sf::Color::White);
  cars[5].setCharacterSize(20);
  cars[5].setPosition(400, 450);

  cars[6].setFont(font);
  cars[6].setString("Sauber");
  cars[6].setFillColor(sf::Color::White);
  cars[6].setCharacterSize(20);
  cars[6].setPosition(400, 500);

  cars[7].setFont(font);
  cars[7].setString("VCARB");
  cars[7].setFillColor(sf::Color::White);
  cars[7].setCharacterSize(20);
  cars[7].setPosition(400, 550);

  cars[8].setFont(font);
  cars[8].setString("Haas");
  cars[8].setFillColor(sf::Color::White);
  cars[8].setCharacterSize(20);
  cars[8].setPosition(400, 600);

  cars[9].setFont(font);
  cars[9].setString("Alipne");
  cars[9].setFillColor(sf::Color::White);
  cars[9].setCharacterSize(20);
  cars[9].setPosition(400, 650);

  selectedCar = 0;
  selectedTrack = 0;
}

void Setup::draw(sf::RenderWindow *window)
{
  for (int i = 0; i < 11; i++)
  {
    window->draw(tracks[i]);
    tracks[selectedTrack].setFillColor(sf::Color::Blue);
  }
  for (int j = 0; j < 10; j++)
  {
    window->draw(cars[j]);
    cars[selectedCar].setFillColor(sf::Color::Blue);
  }
}

void Setup::moveUpTrack()
{
  if (selectedTrack >= 0)
  {
    tracks[selectedTrack].setFillColor(sf::Color::White);

    selectedTrack--;
    if (selectedTrack == -1)
    {
      selectedTrack = 10;
    }
    tracks[selectedTrack].setFillColor(sf::Color::Blue);
  }
}

void Setup::moveDownTrack()
{
  if (selectedTrack <= 11)
  {
    tracks[selectedTrack].setFillColor(sf::Color::White);
    selectedTrack++;
    if (selectedTrack == 11)
    {
      selectedTrack = 0;
    }
    tracks[selectedTrack].setFillColor(sf::Color::Blue);
  }
}

void Setup::moveUpCar()
{
  if (selectedCar >= 0)
  {
    cars[selectedCar].setFillColor(sf::Color::White);

    selectedCar--;
    if (selectedCar == -1)
    {
      selectedCar = 9;
    }
    cars[selectedCar].setFillColor(sf::Color::Blue);
  }
}

void Setup::moveDownCar()
{
  if (selectedCar <= 10)
  {
    cars[selectedCar].setFillColor(sf::Color::White);
    selectedCar++;
    if (selectedCar == 10)
    {
      selectedCar = 0;
    }
    cars[selectedCar].setFillColor(sf::Color::Blue);
  }
}

int Setup::getSelectedTrack()
{
  return this->selectedTrack;
}

int Setup::getSelectedCar()
{
  return this->selectedCar;
}

Setup::~Setup(){};