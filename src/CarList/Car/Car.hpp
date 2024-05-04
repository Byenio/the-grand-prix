#pragma once

#include <iostream>

class Car
{
  int id;
  std::string name;

public:
  Car(const int id, const std::string name);
  ~Car();

  int getId() const;
  std::string getName() const;
};