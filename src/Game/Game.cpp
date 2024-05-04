#include "Game.hpp"

Game::Game(sf::RenderWindow *pWindow) : pWindow(pWindow)
{
  std::string trackListFile = "src/config/tracklist";
  auto pTracks = std::make_shared<TrackList>(trackListFile);
  std::cout << "Successfully initialized tracklist [entries: " << pTracks->size() << "]" << std::endl;

  this->pTracks = pTracks;

  std::string carListFile = "src/config/carlist";
  auto pCars = std::make_shared<CarList>(carListFile);
  std::cout << "Successfully initialized carlist [entries: " << pCars->size() << "]" << std::endl;

  this->pCars = pCars;

  std::cout << "Successfully created game" << std::endl;
};

Game::~Game(){};

void Game::startSession(int trackId, int carId)
{
  std::shared_ptr<Track> selectedTrack = this->pTracks->getTrack(trackId);
  std::shared_ptr<Car> selectedCar = this->pCars->getCar(carId);

  // auto session = std::make_shared<Session>(0, selectedTrack, selectedCar);
  Session *session = new Session(0, selectedTrack, selectedCar);
  this->pSession = session;
};

void Game::closeSession()
{
  std::ofstream file;
  file.open("src/config/sessions", std::ios_base::app);

  file << this->pSession->getId() << "," << this->pSession->getTrack()->getName() << ","
       << this->pSession->getCar()->getName();

  file.close();

  std::cout << "Successfully closed session" << std::endl;

  delete pSession;
}

void Game::closeGame()
{
  this->pWindow->close();
  std::cout << "Successfully closed game" << std::endl;
};