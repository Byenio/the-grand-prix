#pragma once

#include <iostream>

class Car
{
  int id;
  std::string name;

public:
  Car(int id, std::string name);
  ~Car();
};