#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 720), "The Grand Prix");

  Game *pGame = new Game(&window);

  pGame->startSession(3, 3);
  pGame->closeSession();

  pGame->closeGame();
  delete pGame;

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.display();
  }

  return 0;
};