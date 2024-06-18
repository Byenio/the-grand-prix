#include "Setup.hpp"

struct CarData
{
  int id;
  std::string name;
  std::string texturePath;
};

struct TrackData
{
  int id;
  std::string name;
};

Setup::Setup() : selectedTrack(0), selectedCar(0)
{
  if (!font.loadFromFile("assets/fonts/JetBrainsMono.ttf"))
  {
    std::cerr << "Couldn't load font" << std::endl;
  }

  std::ifstream trackFile("config/tracklist");
  if (!trackFile.is_open())
  {
    std::cerr << "Couldn't open track file: config/tracklist" << std::endl;
    return;
  }

  std::string line;
  int trackIndex = 0;

  while (std::getline(trackFile, line))
  {
    std::stringstream ss(line);
    std::string field;

    std::getline(ss, field, ',');
    std::getline(ss, field, ',');

    sf::Text trackText;
    trackText.setFont(font);
    trackText.setString(field);
    trackText.setFillColor(sf::Color::White);
    trackText.setCharacterSize(16);
    trackText.setPosition(200, 200 + trackIndex * 50);

    tracks.push_back(trackText);

    trackIndex++;
  }

  std::ifstream carFile("config/carlist");
  if (!carFile.is_open())
  {
    std::cerr << "Couldn't open car file: config/carlist" << std::endl;
    return;
  }

  int carIndex = 0;

  while (std::getline(carFile, line))
  {
    std::stringstream ss(line);
    std::string field;

    std::getline(ss, field, ',');
    std::getline(ss, field, ',');

    sf::Text carText;
    carText.setFont(font);
    carText.setString(field);
    carText.setFillColor(sf::Color::White);
    carText.setCharacterSize(20);
    carText.setPosition(400, 200 + carIndex * 50);

    cars.push_back(carText);

    carIndex++;
  }
}

Setup::~Setup(){};

void Setup::draw(sf::RenderWindow *window)
{
  for (int i = 0; i < static_cast<int>(tracks.size()); i++)
  {
    window->draw(tracks[i]);
    if (i == selectedTrack)
      tracks[selectedTrack].setFillColor(sf::Color::Blue);
  }
  for (int j = 0; j < static_cast<int>(cars.size()); j++)
  {
    window->draw(cars[j]);
    if (j == selectedCar)
      cars[selectedCar].setFillColor(sf::Color::Blue);
  }
}

void Setup::moveUpTrack()
{
  if (selectedTrack > 0)
  {
    tracks[selectedTrack].setFillColor(sf::Color::White);
    selectedTrack--;
    tracks[selectedTrack].setFillColor(sf::Color::Blue);
  }
}

void Setup::moveDownTrack()
{
  if (selectedTrack < static_cast<int>(tracks.size() - 1))
  {
    tracks[selectedTrack].setFillColor(sf::Color::White);
    selectedTrack++;
    tracks[selectedTrack].setFillColor(sf::Color::Blue);
  }
}

void Setup::moveUpCar()
{
  if (selectedCar > 0)
  {
    cars[selectedCar].setFillColor(sf::Color::White);
    selectedCar--;
    cars[selectedCar].setFillColor(sf::Color::Blue);
  }
}

void Setup::moveDownCar()
{
  if (selectedCar < static_cast<int>(cars.size() - 1))
  {
    cars[selectedCar].setFillColor(sf::Color::White);
    selectedCar++;
    cars[selectedCar].setFillColor(sf::Color::Blue);
  }
}

int Setup::getSelectedTrack()
{
  return selectedTrack;
}

int Setup::getSelectedCar()
{
  return selectedCar;
}