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
    std::vector<std::string> row = fileLineToVector(line, 5);
    auto pCar = std::make_shared<Car>(std::stoi(row[0]), row[1], row[2], std::stoi(row[3]), std::stof(row[4]));
    this->cars.push_back(pCar);
  }

  file.close();
};

CarList::~CarList(){};

std::vector<std::shared_ptr<Car>> CarList::getCars() const
{
  return this->cars;
}

std::shared_ptr<Car> CarList::getCar(const int id) const
{
  auto it =
      std::find_if(cars.begin(), cars.end(), [id](const std::shared_ptr<Car> &ptr) { return ptr->getId() == id; });

  if (it != cars.end())
  {
    return *it;
  }

  return nullptr;
}

int CarList::size() const
{
  return this->cars.size();
}