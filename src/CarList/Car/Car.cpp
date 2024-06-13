#include "Car.hpp"

Car::Car(const int id, const std::string name, const std::string texturePath, const int horsepower, const float grip)
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

  this->tyres.push_back(std::make_shared<Tyre>(305, grip));
  this->tyres.push_back(std::make_shared<Tyre>(305, grip));
  this->tyres.push_back(std::make_shared<Tyre>(405, grip));
  this->tyres.push_back(std::make_shared<Tyre>(405, grip));
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

std::vector<std::shared_ptr<Tyre>> Car::getTyres() const
{
  return this->tyres;
}

std::shared_ptr<Physics> Car::getPhysics() const
{
  return this->physics;
}

void Car::update()
{
  const float speed = this->physics->getSpeed();
  const float angleInRad = this->sprite->getRotation() * 0.0174532925;

  this->sprite->move(this->physics->getVelocity());
  this->sprite->rotate(this->physics->getSpeed() * this->physics->getSteeringAngle());
}

void Car::accelerate()
{
  this->physics->setAcceleration(this->engine->getPower(), this->sprite->getRotation() * 0.0174532925);
  this->update();
};

void Car::decelerate()
{
  if (this->physics->getSpeed() != 0)
  {
    this->physics->setAcceleration(0, this->sprite->getRotation() * 0.0174532925);
  }
  this->update();
}

void Car::negativeDecelerate()
{
  if (this->physics->getSpeed() != 0)
  {
    this->physics->setNegativeAcceleration(0, this->sprite->getRotation() * 0.0174532925);
  }
  this->update();
}

void Car::brake()
{
  this->physics->setAcceleration(-100, this->sprite->getRotation() * 0.0174532925);
  this->update();
}

void Car::reverse()
{
  this->physics->setNegativeAcceleration(100000, this->sprite->getRotation() * 0.0174532925);
  this->update();
}

void Car::turnLeft()
{
<<<<<<< Updated upstream
  this->physics->setSteeringAngle(-this->steeringAngle);
  this->decelerate();
=======
  // this->physics->setSteeringAngle(-this->steeringAngle);
  // this->decelerate();
  float angle = this->physics->turnAngle(MASS, LIFT_COEFF, FRONTAL_AREA,FRICTION_COEFF);
  this->sprite->rotate(-angle);
  std::cout << "angle: " << this->sprite->getRotation() << std::endl;
>>>>>>> Stashed changes
  this->update();
}

void Car::turnRight()
{
<<<<<<< Updated upstream
  this->physics->setSteeringAngle(this->steeringAngle);
  this->decelerate();
=======
  // this->physics->setSteeringAngle(this->steeringAngle);
  // this->decelerate();
  float angle = this->physics->turnAngle(MASS, LIFT_COEFF, FRONTAL_AREA,FRICTION_COEFF);
  this->sprite->rotate(angle);
  std::cout << "angle: " << this->sprite->getRotation() << std::endl;
>>>>>>> Stashed changes
  this->update();
}