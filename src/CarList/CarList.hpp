#pragma once

#include "../utils/functions.hpp"
#include "Car/Car.hpp"
#include <algorithm>
#include <fstream>
#include <memory>

class CarList
{
  std::vector<std::shared_ptr<Car>> carList;

public:
  CarList(std::string &fileName);
  ~CarList();

  int size();
};