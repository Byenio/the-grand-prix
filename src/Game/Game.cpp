#include "Game.hpp"

Game::Game(sf::RenderWindow *pWindow) : pWindow(pWindow)
{
  std::string trackListFile = "src/config/tracklist";
  auto trackList = std::make_shared<TrackList>(trackListFile);
  std::cout << "Successfully initialized tracklist [entries: " << trackList->size() << "]" << std::endl;

  this->pTrackList = trackList;

  std::string carListFile = "src/config/carlist";
  auto carList = std::make_shared<CarList>(carListFile);
  std::cout << "Successfully initialized carlist [entries: " << carList->size() << "]" << std::endl;

  this->pCarList = carList;

  std::cout << "Successfully created game" << std::endl;
};

Game::~Game(){};

std::shared_ptr<Track> Game::selectTrack(int id)
{
  return this->pTrackList->getTrack(id);
}

void Game::close()
{
  this->pWindow->close();
  std::cout << "Successfully closed game" << std::endl;
};