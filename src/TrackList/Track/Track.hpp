#pragma once

#include <iostream>

class Track
{
  int id;
  std::string name;

public:
  Track(int id, std::string name);
  ~Track();

  int getId();
  std::string getName();
};