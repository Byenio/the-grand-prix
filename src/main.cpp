#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(1600, 1000), "The Grand Prix");

  int scale = 4;
  int textureSize = 64;
  int centerX = (window.getSize().x - textureSize * scale) / 2;
  int centerY = (window.getSize().y - textureSize * scale) / 2;

  Game *pGame = new Game(&window);

  pGame->startSession(3, 3);

  pGame->getCar()->getSprite()->setScale(scale, scale);
  pGame->getCar()->getSprite()->setPosition(centerX, centerY);

  // pGame->closeSession();
  // pGame->closeGame();
  // delete pGame;

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
      pGame->getCar()->moveForward();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
      pGame->getCar()->moveBackward();
    }

    window.clear(sf::Color::White);
    window.draw(*pGame->getCar()->getSprite());
    window.display();
  }

  return 0;
};