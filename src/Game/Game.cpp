#include "Game.hpp"

Game::Game(sf::RenderWindow *pWindow) : pWindow(pWindow)
{
  std::string trackListFile = "config/tracklist";
  this->pTracks = std::make_unique<TrackList>(trackListFile);
  std::cout << "Successfully initialized tracklist [entries: " << this->pTracks->size() << "]" << std::endl;

  std::string carListFile = "config/carlist";
  this->pCars = std::make_unique<CarList>(carListFile);
  std::cout << "Successfully initialized carlist [entries: " << this->pCars->size() << "]" << std::endl;

  std::cout << "Successfully created game" << std::endl;
};

Game::~Game(){};

void Game::startSession(int trackId, int carId)
{
  std::shared_ptr<Track> selectedTrack = this->pTracks->getTrack(trackId);
  std::shared_ptr<Car> selectedCar = this->pCars->getCar(carId);

  this->pSession = std::make_unique<Session>(0, selectedTrack, selectedCar);
  std::cout << "Successfully started session: [" << this->pSession->getTrack()->getName() << ", "
            << this->pSession->getCar()->getName() << "]" << std::endl;
};

std::shared_ptr<Session> Game::getSession()
{
  return this->pSession;
}

std::shared_ptr<Car> Game::getCar()
{
  return this->pSession->getCar();
}