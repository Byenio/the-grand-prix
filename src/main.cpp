#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 720), "The Grand Prix");

  Game *game = new Game(&window);

  std::cout << game->selectTrack(3)->getName() << std::endl;

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