#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Racetrack.hpp"
#include "Session/Lap/Lap.hpp"
#include "Session/Player/Player.hpp"
#include "Session/Session.hpp"

// Game *gameInit(sf::RenderWindow &rWindow)
// {
//   Player *pPlayer = new Player("byenio", 13);
//   Racetrack *pRacetrack = new Racetrack("monza");
//   Session *pSession = new Session(pPlayer, pRacetrack);

//   Lap *pLap1 = new Lap(pPlayer, pRacetrack, 53000);
//   Lap *pLap2 = new Lap(pPlayer, pRacetrack, 53001);
//   Lap *pLap3 = new Lap(pPlayer, pRacetrack, 52999);

//   pSession->pushLap(pLap1);
//   pSession->pushLap(pLap2);
//   pSession->pushLap(pLap3);

//   sf::CircleShape circle(100.f);
//   circle.setFillColor(sf::Color::Red);
//   circle.setPosition(600, 200);

//   rWindow.clear();
//   rWindow.draw(circle);
//   rWindow.display();

//   Game *pGame = new Game();

//   return pGame;
// };

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 720), "The Grand Prix");

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
  }

  return 0;
};