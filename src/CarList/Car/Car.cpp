#include "Car.hpp"

Car::Car(const int id, const std::string name, const std::string texturePath, const int horsepower)
    : id(id), name(name), texture(std::make_shared<sf::Texture>()), sprite(std::make_shared<sf::Sprite>())
{
  // std::cout << "Successfully created new car: [" << id << "] " <<
  // name << std::endl;
  if (!texture->loadFromFile(texturePath))
  {
    std::cout << "Couldn't load texture from file: " << texturePath << std::endl;
  }

  sprite->setTexture(*texture);
  sf::FloatRect bounds = sprite->getLocalBounds();
  sprite->setOrigin(bounds.width / 2, bounds.height / 2);

  this->physics = std::make_shared<Physics>();
  this->engine = std::make_shared<Engine>(horsepower);
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
  return this->sprite;
}

std::shared_ptr<Engine> Car::getEngine() const
{
  return this->engine;
}

std::shared_ptr<Physics> Car::getPhysics() const
{
  return this->physics;
}

void Car::update()
{
  const float speed = this->physics->getSpeed();
  const float angleInRad = this->sprite->getRotation() * 0.0174532925;
  sf::Vector2f movement(speed * sin(angleInRad), -speed * cos(angleInRad));

  this->sprite->move(movement);
  this->sprite->rotate(this->physics->getSpeed() * this->physics->getSteeringAngle());
}

void Car::accelerate()
{
  this->physics->setAcceleration(this->acceleration - this->dragAcceleration);
  this->update();
};

void Car::decelerate()
{
  if (this->physics->getSpeed() != 0)
  {
    this->physics->setAcceleration(this->dragAcceleration * this->physics->getSign());
  }
  this->update();
}

void Car::brake()
{
  this->physics->setAcceleration((this->brakeAcceleration + this->dragAcceleration) * this->physics->getSign());
  this->update();
}

void Car::reverse()
{
  this->physics->setAcceleration(this->reverseAcceleration - this->dragAcceleration);
  this->update();
}

void Car::turnLeft()
{
  this->physics->setSteeringAngle(-this->steeringAngle);
  this->decelerate();
  this->update();
}

void Car::turnRight()
{
  this->physics->setSteeringAngle(this->steeringAngle);
  this->decelerate();
  this->update();
}