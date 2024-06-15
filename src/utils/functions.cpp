#include "functions.hpp"

std::vector<std::string> fileLineToVector(const std::string &line, const int cols)
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

bool noAccelerationKeyPressed()
{
  return (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S));
}

bool noSteeringKeyPressed()
{
  return (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D));
}

bool isZero(float value, float epsilon)
{
  return std::abs(value) < epsilon;
}

std::string generateFilename()
{
  std::time_t now = std::time(nullptr);
  std::tm localTime;
  localtime_s(&localTime, &now);

  std::stringstream ss;
  ss << std::put_time(&localTime, "%Y-%m-%d_%H-%M-%S");

  std::string filename = "session_" + ss.str();

  return filename;
}

std::string formatTime(int timeMs)
{
  int minutes = timeMs / 60000;
  int seconds = (timeMs / 1000) % 60;
  int milliseconds = timeMs % 1000;

  std::stringstream ss;
  ss << minutes << ":" << std::setw(2) << std::setfill('0') << seconds << "." << std::setw(3) << std::setfill('0')
     << milliseconds;

  return ss.str();
}