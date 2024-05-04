#include "CarList.hpp"

CarList::CarList(const std::string &fileName)
{
  std::ifstream file(fileName);

  if (!file.is_open())
  {
    throw std::runtime_error("Failed to open file: " + fileName);
  }

  std::string line;

  while (getline(file, line))
  {
    std::vector<std::string> row = vectorizeLine(line);
    auto pCar = std::make_shared<Car>(std::stoi(row[0]), row[1]);
    this->cars.push_back(pCar);
  }

  file.close();
};

CarList::~CarList(){};

std::shared_ptr<Car> CarList::getCar(const int id) const
{
  return this->cars.at(id);
}

int CarList::size() const
{
  return this->cars.size();
}