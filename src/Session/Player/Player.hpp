#pragma once

#include <iostream>
#include <string>

class Player
{
  static int sID;
  int id;
  std::string name;
  int racingNumber;

public:
  Player(std::string name, int racingNumber);
  virtual ~Player();

  int getId();
};