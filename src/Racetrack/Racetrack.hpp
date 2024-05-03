#pragma once

#include <iostream>
#include <string>

class Racetrack
{
  static int sID;
  int id;
  std::string name;

public:
  Racetrack(std::string name);
  virtual ~Racetrack();

  int getId();
  std::string getName();
};