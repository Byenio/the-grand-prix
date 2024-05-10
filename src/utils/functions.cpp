#include "functions.hpp"

std::vector<std::string> vectorizeLine(const std::string &line, const int cols)
{
  char delimiter = ',';
  std::stringstream ssLine(line);
  std::string temp;
  std::vector<std::string> row;
  int i = 0;

  while (getline(ssLine, temp, delimiter))
  {
    row.push_back(temp);
    i += 1;
    i = i % cols;
  };

  return row;
};