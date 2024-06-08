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
  int tickrate = 30;
  float oldTime = 0;

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

  Game game(&window);

  game.startSession(1, 1);

  json trackModel = game.getSession()->getTrackModel();

  std::vector<sf::RectangleShape> trackSegments;
  std::vector<TrackSectors> trackSectorLines;
  // track segments generation
  for (auto &segment : trackModel[0]["shapes"])
  {
    float trackScale = 100;

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
    float trackScale = 100;

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

  game.getCar()->getSprite()->setScale(scale, scale);
  game.getCar()->getSprite()->setPosition(7200, 3300);

  // game.closeSession();
  // game.closeGame();
  // delete game;

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // session timer
    float newTime = game.getSession()->getClock().getElapsedTime().asMilliseconds();
    float delta = newTime - oldTime;

    if (delta >= tickrate)
    {
      oldTime = newTime;

      // update physics
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      {
        // if stopped or moving forward
        // accelerate
        game.getCar()->accelerate();

        // if moving backward
        // brake
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      {
        // if moving forward
        // brake
        game.getCar()->brake();

        // if stopped or moving rearward
        // delay(ie 0.5s) or accelerate
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      {
        // turn left
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      {
        // turn right
      }

      if (noAccelerationKeyPressed())
      {
        // decelerate
        game.getCar()->decelerate();
      }

      if (noSteeringKeyPressed())
      {
        // go straight
      }
    }

    std::string speedString = std::to_string(static_cast<int>(game.getCar()->getPhysics()->getSpeed() * 3.6));
    speed.setString(speedString + " km/h");

    view.setCenter(game.getCar()->getSprite()->getPosition());
    speed.setPosition(view.getCenter().x + 700, view.getCenter().y + 460);

    window.setView(view);
    window.clear(sf::Color::White);

    bool offtrack = true;

    for (auto &segment : trackSegments)
    {
      window.draw(segment);

      if (game.getCar()->getSprite()->getGlobalBounds().intersects(segment.getGlobalBounds()))
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

      if (game.getCar()->getSprite()->getGlobalBounds().intersects(sectorLine.shape.getGlobalBounds()))
      {
        currentSector = sectorLine.num;
      }
    }

    window.draw(*game.getCar()->getSprite());
    window.draw(speed);
    window.display();
  }

  return 0;
};
