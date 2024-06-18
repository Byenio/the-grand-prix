#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> fileLineToVector(const std::string &line, const int cols);

bool noAccelerationKeyPressed();
bool noSteeringKeyPressed();
bool isZero(float value, float epsilon);

std::string formatTime(int timeMs);

std::string generateFilename();
void updateSessionLapsToFile(const std::vector<std::vector<int>> &sessionLaps, const std::string &filename);