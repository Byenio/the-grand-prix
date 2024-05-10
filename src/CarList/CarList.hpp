#pragma once

#include <algorithm>
#include <fstream>
#include <memory>

#include "../utils/functions.hpp"
#include "Car/Car.hpp"

class CarList
{
  std::vector<std::shared_ptr<Car>> cars;

public:
  CarList(const std::string &fileName);
  ~CarList();

  std::vector<std::shared_ptr<Car>> getCars() const;
  std::shared_ptr<Car> getCar(const int id) const;

  int size() const;
};