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
  this->sprite->move(this->physics->getVelocity());
  this->sprite->rotate(this->rotation * RAD_TO_DEG);
}

void Car::accelerate()
{
  float enginePower = this->engine->getPower() * 0.9f;
  float rotation = (360 - this->sprite->getRotation()) * DEG_TO_RAD;

  this->physics->accelerate(enginePower, MASS, DRAG_COEFF, LIFT_COEFF, FRONTAL_AREA, ROLL_COEFF, FRICTION_COEFF,
                            rotation);
};

void Car::decelerate()
{
  float rotation = (360 - this->sprite->getRotation()) * DEG_TO_RAD;
  this->physics->decelerate(MASS, DRAG_COEFF, LIFT_COEFF, FRONTAL_AREA, ROLL_COEFF, FRICTION_COEFF, rotation);
}

void Car::brake()
{
  float rotation = (360 - this->sprite->getRotation()) * DEG_TO_RAD;
  this->physics->brake(MASS, DRAG_COEFF, LIFT_COEFF, FRONTAL_AREA, ROLL_COEFF, FRICTION_COEFF, BRAKE_COEFF, rotation);
}

void Car::reverse()
{
  float enginePower = 15000 * 0.9f;
  float rotation = (360 - this->sprite->getRotation()) * DEG_TO_RAD;

  this->physics->accelerate(enginePower, MASS, DRAG_COEFF, LIFT_COEFF, FRONTAL_AREA, ROLL_COEFF, FRICTION_COEFF,
                            rotation);
}

void Car::turnLeft()
{
  this->rotation = this->physics->turnAngle(MASS, LIFT_COEFF, FRONTAL_AREA, FRICTION_COEFF, -1);
}

void Car::turnRight()
{
  this->rotation = this->physics->turnAngle(MASS, LIFT_COEFF, FRONTAL_AREA, FRICTION_COEFF, 1);
}

float Car::getRotation()
{
  return this->rotation;
}

void Car::setRotation(float angle)
{
  this->rotation = angle;
}