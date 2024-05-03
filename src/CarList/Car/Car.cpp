#include "Car.hpp"

Car::Car(int id, std::string name) : id(id), name(name)
{
  std::cout << "Successfully created new car: [" << id << "] " << name << std::endl;
};

Car::~Car(){};