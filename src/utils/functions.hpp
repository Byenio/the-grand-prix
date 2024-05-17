#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> vectorizeLine(const std::string &line, const int cols);

bool noAccelerationKeyPressed();
bool noSteeringKeyPressed();
bool isZero(float value, float epsilon);