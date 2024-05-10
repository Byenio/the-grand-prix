#include "Car.hpp"

Car::Car(const int id, const std::string name, const std::string texturePath)
    : id(id), name(name), texture(std::make_shared<sf::Texture>()), sprite(std::make_shared<sf::Sprite>())
{
  // std::cout << "Successfully created new car: [" << id << "] " <<
  // name << std::endl;
  if (!texture->loadFromFile(texturePath))
  {
    std::cout << "Couldn't load texture from file: " << texturePath << std::endl;
  }

  sprite->setTexture(*texture);
};

Car::~Car(){};

int Car::getId() const
{
  return this->id;
}

std::string Car::getName() const
{
  return this->name;
}

std::shared_ptr<sf::Sprite> Car::getSprite() const
{
  return sprite;
}

void Car::moveForward()
{
  this->sprite->setPosition(sprite->getPosition().x, sprite->getPosition().y - 0.1f);
}

void Car::moveBackward()
{
  this->sprite->setPosition(sprite->getPosition().x, sprite->getPosition().y + 0.1f);
}