#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main()
{

  sf::RenderWindow window(sf::VideoMode(1600, 1000), "The Grand Prix");
  sf::View view = window.getDefaultView();
  window.setFramerateLimit(20);
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

  Game *pGame = new Game(&window);

  pGame->startSession(3, 1);

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
      pGame->getCar()->getPhysics()->setTractionForce(0, pGame->getCar()->getSprite()->getRotation());

      if (!isZero(pGame->getCar()->getPhysics()->getSpeed(), 1e-1f))
      {
        pGame->getCar()->decelerate();
      }

      if (isZero(pGame->getCar()->getPhysics()->getSpeed(), 1e-1f))
      {
        pGame->getCar()->getPhysics()->setSpeed(0);
      }
    }

    if (noSteeringKeyPressed())
    {
      pGame->getCar()->getPhysics()->setSteeringAngle(0);
    }

    std::string speedString = std::to_string(static_cast<int>(pGame->getCar()->getPhysics()->getSpeed() * 3.6));
    speed.setString(speedString + " km/h");

    std::cout << pGame->getCar()->getPhysics()->getAcceleration() << "|" << pGame->getCar()->getPhysics()->getSpeed()
              << std::endl;

    view.setCenter(pGame->getCar()->getSprite()->getPosition());
    speed.setPosition(view.getCenter().x + 700, view.getCenter().y + 460);

    window.setView(view);
    window.clear(sf::Color::White);
    window.draw(*pGame->getCar()->getSprite());
    window.draw(speed);
    window.display();
  }

  return 0;
};
