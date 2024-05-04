#pragma once

#include <iostream>

class Track
{
  int id;
  std::string name;

public:
  Track(const int id, const std::string name);
  ~Track();

  int getId() const;
  std::string getName() const;
};