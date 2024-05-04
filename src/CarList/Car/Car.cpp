#include "Car.hpp"

Car::Car(const int id, const std::string name)
    : id(id), name(name){
                  // std::cout << "Successfully created new car: [" << id << "] " <<
                  // name << std::endl;
              };

Car::~Car(){};

int Car::getId() const
{
  return this->id;
}

std::string Car::getName() const
{
  return this->name;
}