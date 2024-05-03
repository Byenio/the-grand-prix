#include "CarList.hpp"

CarList::CarList(std::string &fileName)
{
  std::string line;
  std::ifstream file(fileName);

  while (getline(file, line))
  {
    std::vector<std::string> row = vectorizeLine(line);
    auto car = std::make_shared<Car>(std::stoi(row[0]), row[1]);
    this->carList.push_back(car);
  }

  file.close();
};

CarList::~CarList(){};

int CarList::size()
{
  return this->carList.size();
}