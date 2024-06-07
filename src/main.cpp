#include "Game.hpp"
#include "utils/json.hpp"
#include <SFML/Graphics.hpp>

using json = nlohmann::json;

struct TrackSectors
{
  sf::RectangleShape shape;
  int num;
};

int main()
{
  sf::RenderWindow window(sf::VideoMode(1600, 1000), "The Grand Prix");
  sf::View view = window.getDefaultView();
  window.setFramerateLimit(60);
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

  pGame->startSession(1, 1);

  json trackModel = pGame->getSession()->getTrackModel();

  std::vector<sf::RectangleShape> trackSegments;
  std::vector<TrackSectors> trackSectorLines;
  // track segments generation
  for (auto &segment : trackModel[0]["shapes"])
  {
    float trackScale = 4;

    float width = segment["width"];
    float height = segment["height"];
    float x = segment["x"];
    float y = segment["y"];
    sf::RectangleShape shape(sf::Vector2f(width * trackScale, height * trackScale));
    shape.setPosition(sf::Vector2f(x * trackScale, y * trackScale));
    shape.setFillColor(sf::Color(sf::Color::Red));

    trackSegments.push_back(shape);
  }

  // track sector lines generation
  for (auto &sectorLine : trackModel[0]["sectors"])
  {
    float trackScale = 4;

    float width = sectorLine["width"];
    float height = sectorLine["height"];
    float x = sectorLine["x"];
    float y = sectorLine["y"];
    int num = sectorLine["num"];
    bool isFinishLine = sectorLine["isFinishLine"];

    sf::RectangleShape shape(sf::Vector2f(width * trackScale, height * trackScale));
    shape.setPosition(sf::Vector2f(x * trackScale, y * trackScale));
    shape.setFillColor(sf::Color(sf::Color::Black));

    if (isFinishLine)
    {
      shape.setFillColor(sf::Color(sf::Color::White));
    }

    TrackSectors sector = {shape, num};

    trackSectorLines.push_back(sector);
  }

  int currentSector = 1;

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
      pGame->getCar()->getPhysics()->setTractionForce(0);

      if (!isZero(pGame->getCar()->getPhysics()->getSpeed(), 1e-1f))
      {
        pGame->getCar()->decelerate();
      }

      // if (isZero(pGame->getCar()->getPhysics()->getSpeed(), 1e-1f))
      // {
      //   pGame->getCar()->getPhysics()->setSpeed();
      // }
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

    bool offtrack = true;

    for (auto &segment : trackSegments)
    {
      window.draw(segment);

      if (pGame->getCar()->getSprite()->getGlobalBounds().intersects(segment.getGlobalBounds()))
      {
        offtrack = false;
      }
    }

    if (offtrack)
    {
      std::cout << "OFFTRACK" << std::endl;
    }

    for (auto &sectorLine : trackSectorLines)
    {
      window.draw(sectorLine.shape);

      if (pGame->getCar()->getSprite()->getGlobalBounds().intersects(sectorLine.shape.getGlobalBounds()))
      {
        currentSector = sectorLine.num;
      }
    }

    std::cout << currentSector << std::endl;

    window.draw(*pGame->getCar()->getSprite());
    window.draw(speed);
    window.display();
  }

  return 0;
};
