#include "Player.hpp"

Player::Player(std::string name, int racingNumber) : id(sID++), name(name), racingNumber(racingNumber)
{
  std::cout << "Successfully created player: " << name << " (" << racingNumber << ")" << std::endl;
};

Player::~Player(){};

int Player::getId()
{
  return this->id;
}

int Player::sID = 0;