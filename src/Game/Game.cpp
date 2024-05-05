#include "Game.hpp"

Game::Game(sf::RenderWindow *pWindow) : pWindow(pWindow)
{
  std::string trackListFile = "src/config/tracklist";
  this->pTracks = std::make_unique<TrackList>(trackListFile);
  std::cout << "Successfully initialized tracklist [entries: " << this->pTracks->size() << "]" << std::endl;

  std::string carListFile = "src/config/carlist";
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

void Game::closeSession()
{
  std::ofstream file;
  file.open("src/config/sessions", std::ios_base::app);

  file << this->pSession->getId() << "," << this->pSession->getTrack()->getName() << ","
       << this->pSession->getCar()->getName();

  file.close();

  std::cout << "Successfully closed session" << std::endl;

  this->pSession.reset();
}

void Game::closeGame()
{
  this->pWindow->close();
  std::cout << "Successfully closed game" << std::endl;
};