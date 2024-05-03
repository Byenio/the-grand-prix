#include "Game.hpp"

Game::Game()
{
  std::cout << "Successfully created a new game" << std::endl;
};

Game::~Game(){};

void Game::close(sf::RenderWindow &rWindow)
{
  rWindow.close();
}