#include "Game.hpp"
#include "Menu/Menu.hpp"
#include "Setup/Setup.hpp"
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
  sf::RenderWindow menuWindow(sf::VideoMode(960, 720), "Menu");
  Menu menu(menuWindow.getSize().x, menuWindow.getSize().y);

  while (menuWindow.isOpen())
  {
    sf::Event event;
    while (menuWindow.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        menuWindow.close();
      }

      if (event.type == sf::Event::KeyReleased)
      {
        if (event.key.code == sf::Keyboard::Up)
        {
          menu.moveUp();
          break;
        }
        if (event.key.code == sf::Keyboard::Down)
        {
          menu.moveDown();
          break;
        }
        if (event.key.code == sf::Keyboard::Return)
        {

          int x = menu.menuPressed();
          if (x == 0)
          {
            sf::RenderWindow setupWindow(sf::VideoMode(960, 720), "Setup");
            Setup setup(setupWindow.getSize().x, setupWindow.getSize().y);

            while (setupWindow.isOpen())
            {
              sf::Event sevent;
              while (setupWindow.pollEvent(sevent))
              {
                if (sevent.type == sf::Event::Closed)
                {
                  setupWindow.close();
                }

                if (sevent.type == sf::Event::KeyReleased)
                {
                  if (sevent.key.code == sf::Keyboard::Up)
                  {
                    setup.moveUpCar();
                    break;
                  }
                  if (sevent.key.code == sf::Keyboard::Down)
                  {
                    setup.moveDownCar();
                    break;
                  }
                  if (sevent.key.code == sf::Keyboard::W)
                  {
                    setup.moveUpTrack();
                    break;
                  }
                  if (sevent.key.code == sf::Keyboard::S)
                  {
                    setup.moveDownTrack();
                    break;
                  }
                  if (sevent.key.code == sf::Keyboard::Return)
                  {
                    int car = setup.getSelectedCar();
                    int track = setup.getSelectedTrack();

                    sf::RenderWindow playWindow(sf::VideoMode(1600, 1000), "The Grand Prix");
                    sf::View view = playWindow.getDefaultView();
                    playWindow.setFramerateLimit(60);
                    int tickrate = 30;
                    float oldTime = 0;

                    int scale = 2;
                    int textureSizeX = 32;
                    int textureSizeY = 64;
                    int centerX = (playWindow.getSize().x - textureSizeX * scale) / 2;
                    int centerY = (playWindow.getSize().y - textureSizeY * scale) / 2;

                    sf::Font font;
                    font.loadFromFile("src/assets/fonts/JetBrainsMono.ttf");

                    sf::Text speed;
                    speed.setFont(font);
                    speed.setCharacterSize(16);
                    speed.setFillColor(sf::Color::Black);

                    sf::Text timer;
                    timer.setFont(font);
                    timer.setCharacterSize(32);
                    timer.setFillColor(sf::Color::Black);

                    sf::Text lastLap;
                    lastLap.setFont(font);
                    lastLap.setCharacterSize(32);
                    lastLap.setFillColor(sf::Color::Black);
                    lastLap.setString("Last: 0:00.000");

                    sf::Text s1time;
                    s1time.setFont(font);
                    s1time.setCharacterSize(16);
                    s1time.setFillColor(sf::Color::Black);
                    s1time.setString("S1: 0:00.000");

                    sf::Text s2time;
                    s2time.setFont(font);
                    s2time.setCharacterSize(16);
                    s2time.setFillColor(sf::Color::Black);
                    s2time.setString("S2: 0:00.000");

                    sf::Text s3time;
                    s3time.setFont(font);
                    s3time.setCharacterSize(16);
                    s3time.setFillColor(sf::Color::Black);
                    s3time.setString("S3: 0:00.000");

                    std::vector<std::vector<int>> sessionLaps;
                    Game game(&playWindow);

                    game.startSession(track, car);

                    json trackModel = game.getSession()->getTrackModel();

                    std::vector<sf::RectangleShape> trackSegments;
                    std::vector<TrackSectors> trackSectorLines;
                    float trackScale = 10;
                    // track segments generation
                    for (auto &segment : trackModel[0]["shapes"])
                    {
                      float width = segment["width"];
                      float height = segment["height"];
                      float x = segment["x"];
                      float y = segment["y"];
                      sf::RectangleShape shape(sf::Vector2f(width * trackScale, height * trackScale));
                      shape.setPosition(sf::Vector2f(x * trackScale, y * trackScale));
                      shape.setFillColor(sf::Color(sf::Color(60, 60, 60)));

                      trackSegments.push_back(shape);
                    }

                    // track sector lines generation
                    for (auto &sectorLine : trackModel[0]["sectors"])
                    {
                      float width = sectorLine["width"];
                      float height = sectorLine["height"];
                      float x = sectorLine["x"];
                      float y = sectorLine["y"];
                      float rotation = sectorLine["rotation"];
                      int num = sectorLine["num"];
                      bool isFinishLine = sectorLine["isFinishLine"];

                      sf::RectangleShape shape(sf::Vector2f(width, height * trackScale));
                      shape.setPosition(sf::Vector2f(x * trackScale, y * trackScale));
                      shape.setFillColor(sf::Color(sf::Color::Black));
                      shape.setRotation(rotation);

                      if (isFinishLine)
                      {
                        shape.setFillColor(sf::Color(sf::Color::Red));
                      }

                      TrackSectors sector = {shape, num};

                      trackSectorLines.push_back(sector);
                    }

                    int previousSector = 3;
                    int currentSector = 3;
                    bool invalidated = true;

                    float spawnX = trackModel[0]["spawn"]["x"];
                    float spawnY = trackModel[0]["spawn"]["y"];
                    float spawnAngle = trackModel[0]["spawn"]["angle"];

                    game.getCar()->getSprite()->setScale(scale, scale);
                    game.getCar()->getSprite()->setPosition(spawnX * trackScale, spawnY * trackScale);
                    game.getCar()->getSprite()->setRotation(spawnAngle);

                    // game.closeSession();
                    // game.closeGame();
                    // delete game;

                    while (playWindow.isOpen())
                    {
                      sf::Event pevent;

                      while (playWindow.pollEvent(pevent))
                      {
                        if (pevent.type == sf::Event::Closed)
                          playWindow.close();
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
                          if (game.getCar()->getPhysics()->getSpeed() >= 0)
                          {
                            game.getCar()->getPhysics()->setPositiveSpeedSign();
                            game.getCar()->accelerate();
                          }
                          // if moving backward
                          // brake
                          else
                          {
                            game.getCar()->brake();
                          }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        {
                          // if moving forward
                          // brake
                          if (game.getCar()->getPhysics()->getSpeed() > 0)
                          {
                            game.getCar()->brake();
                          }
                          // if stopped or moving rearward
                          // delay(ie 0.5s) or accelerate
                          else
                          {
                            game.getCar()->getPhysics()->setNegativeSpeedSign();
                            game.getCar()->reverse();
                          }
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        {
                          // turn left
                          game.getCar()->multiplyRollCoeff(10);
                          game.getCar()->turnLeft();
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        {
                          // turn right
                          game.getCar()->multiplyRollCoeff(10);
                          game.getCar()->turnRight();
                        }

                        if (noAccelerationKeyPressed())
                        {
                          // decelerate
                          if (fabs(game.getCar()->getPhysics()->getSpeed()) > 1.0f)
                          {
                            game.getCar()->decelerate();
                          }
                          else
                          {
                            game.getCar()->getPhysics()->stop();
                          }
                        }

                        if (noSteeringKeyPressed())
                        {
                          // go straight
                          game.getCar()->multiplyRollCoeff(1);
                          game.getCar()->setRotation(0);
                        }

                        game.getCar()->update();
                        std::cout << game.getCar()->getSprite()->getPosition().x << " "
                                  << game.getCar()->getSprite()->getPosition().y << std::endl;
                      }

                      std::string speedString =
                          std::to_string(static_cast<int>(game.getCar()->getPhysics()->getSpeed() * 3.6));
                      speed.setString(speedString + " km/h");

                      view.setCenter(game.getCar()->getSprite()->getPosition());

                      playWindow.setView(view);
                      playWindow.clear(sf::Color::White);

                      bool offtrack = true;

                      for (auto &segment : trackSegments)
                      {
                        playWindow.draw(segment);

                        if (game.getCar()->getSprite()->getGlobalBounds().intersects(segment.getGlobalBounds()))
                        {
                          offtrack = false;
                        }
                      }

                      if (offtrack)
                      {
                        timer.setFillColor(sf::Color::Red);

                        invalidated = true;
                      }

                      for (auto &sectorLine : trackSectorLines)
                      {
                        playWindow.draw(sectorLine.shape);

                        if (game.getCar()->getSprite()->getGlobalBounds().intersects(
                                sectorLine.shape.getGlobalBounds()))
                        {
                          currentSector = sectorLine.num;
                        }
                      }

                      int timeMs = game.getSession()->timer.getElapsedTime().asMilliseconds();

                      int s1TimeDiff, s2TimeDiff, s3TimeDiff, lastLapTime;

                      if (currentSector != previousSector)
                      {
                        // update sector time
                        if (currentSector == 3)
                        {
                          s2TimeDiff = timeMs - s1TimeDiff;
                          s2time.setString("S2: " + formatTime(s2TimeDiff));
                        }

                        if (currentSector == 2)
                        {
                          s1TimeDiff = timeMs;
                          s1time.setString("S1: " + formatTime(s1TimeDiff));
                        }

                        if (currentSector == 1)
                        {
                          s3TimeDiff = timeMs - s1TimeDiff - s2TimeDiff;
                          if (s3TimeDiff < 0)
                          {

                            s3time.setString("S3: " + formatTime(0));
                          }
                          else
                          {
                            s3time.setString("S3: " + formatTime(s3TimeDiff));
                          }

                          // save lap
                          if (!invalidated)
                          {
                            std::string path = "sessions/" + generateFilename();
                            std::cout << path << std::endl;
                            lastLapTime = timeMs;
                            lastLap.setString("Last: " + formatTime(lastLapTime));

                            int id = sessionLaps.size();
                            std::vector<int> lap = {id, lastLapTime, s1TimeDiff, s2TimeDiff, s3TimeDiff};
                            sessionLaps.push_back(lap);
                          }

                          // restart timer
                          game.getSession()->timer.restart();

                          timer.setFillColor(sf::Color::Black);

                          invalidated = false;
                        }
                        previousSector = currentSector;
                      }

                      timer.setString(formatTime(timeMs));

                      speed.setPosition(view.getCenter().x + 700, view.getCenter().y + 460);
                      timer.setPosition(view.getCenter().x - 75, view.getCenter().y - 480);
                      lastLap.setPosition(view.getCenter().x + 520, view.getCenter().y - 480);
                      s1time.setPosition(view.getCenter().x + 672, view.getCenter().y - 440);
                      s2time.setPosition(view.getCenter().x + 672, view.getCenter().y - 425);
                      s3time.setPosition(view.getCenter().x + 672, view.getCenter().y - 410);

                      playWindow.draw(*game.getCar()->getSprite());
                      playWindow.draw(speed);
                      playWindow.draw(timer);
                      playWindow.draw(s1time);
                      playWindow.draw(s2time);
                      playWindow.draw(s3time);
                      playWindow.draw(lastLap);
                      playWindow.display();
                    }

                    return 0;
                  }
                }
              }
              setupWindow.clear();
              setup.draw(setupWindow);
              setupWindow.display();
            }
          };
          if (x == 1)
          {
            sf::RenderWindow leaderboardsWindow(sf::VideoMode(900, 720), "LeaderBoards");
            while (leaderboardsWindow.isOpen())
            {
              sf::Event levent;
              if (levent.type == sf::Event::Closed)
              {
                leaderboardsWindow.close();
              }
              leaderboardsWindow.display();
            }
          }
          if (x == 2)
          {
            menuWindow.close();
          }
        }
      }
    }
    menuWindow.clear();
    menu.draw(menuWindow);
    menuWindow.display();
  }
}
