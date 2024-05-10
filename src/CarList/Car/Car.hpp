#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

class Car
{
  int id;
  std::string name;
  std::shared_ptr<sf::Texture> texture;
  std::shared_ptr<sf::Sprite> sprite;

public:
  Car(const int id, const std::string name, const std::string texturePath);
  ~Car();

  int getId() const;
  std::string getName() const;
  std::shared_ptr<sf::Sprite> getSprite() const;

  void moveForward();
  void moveBackward();
  void turnLeft();
  void turnRight();
};