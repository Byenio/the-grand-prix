#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(1600, 1000), "The Grand Prix");

  int scale = 4;
  int textureSize = 64;
  int centerX = (window.getSize().x - textureSize * scale) / 2;
  int centerY = (window.getSize().y - textureSize * scale) / 2;

  sf::Font font;
  font.loadFromFile("src/assets/fonts/JetBrainsMono.ttf");

  sf::Text speed;
  speed.setFont(font);
  speed.setCharacterSize(16);
  speed.setFillColor(sf::Color::Black);
  speed.setPosition(window.getSize().x - 160, window.getSize().y - 32);

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
      if (pGame->getCar()->getPhysics()->getSign() > 0)
      {
        pGame->getCar()->accelerate();
      }
      else
      {
        pGame->getCar()->brake();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
      if (pGame->getCar()->getPhysics()->getSign() > 0)
      {
        pGame->getCar()->brake();
      }
      else
      {
        pGame->getCar()->reverse();
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
      pGame->getCar()->turnLeft();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
      pGame->getCar()->turnRight();
    }

    if (noAccelerationKeyPressed())
    {
      if (!isZero(pGame->getCar()->getPhysics()->getSpeed(), 1e-3f))
      {
        pGame->getCar()->decelerate();
      }

      if (isZero(pGame->getCar()->getPhysics()->getSpeed(), 1e-3f))
      {
        pGame->getCar()->getPhysics()->setSpeed(0);
      }
    }

    if (noSteeringKeyPressed())
    {
      pGame->getCar()->getPhysics()->setSteeringAngle(0);
    }

    std::string speedString = std::to_string(static_cast<int>(pGame->getCar()->getPhysics()->getSpeed() * 100));
    speed.setString(speedString + " km/h");

    window.clear(sf::Color::White);
    window.draw(*pGame->getCar()->getSprite());
    window.draw(speed);
    window.display();
  }

  return 0;
};
