#include "io.h"
#include <iostream>
#include <limits>
#include <string>

std::string IO::getString(std::string msg) {
  std::string result;
  if (msg == "")
    std::cout << "> ";
  else
    std::cout << msg << ": ";
  std::cin >> result;

  return result;
}

int IO::getInt(std::string msg) {
  int value;
  if (msg == "")
    std::cout << "> ";
  else
    std::cout << msg << ": ";
  if (!(std::cin >> value)) {
    std::cout << "Error: Input is not an integer." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return -1;
  }
  return value;
}

float IO::getFloat(std::string msg) {
  float value;
  if (msg == "")
    std::cout << "> ";
  else
    std::cout << msg << ": ";
  if (!(std::cin >> value)) {
    std::cout << "Error: Input is not a float." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return -1;
  }
  return value;
}

double IO::getDouble(std::string msg) {
  double value;
  if (msg == "")
    std::cout << "> ";
  else
    std::cout << msg << ": ";
  if (!(std::cin >> value)) {
    std::cout << "Error: Input is not a double." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return -1;
  }
  return value;
}

void IO::print(std::string msg) { std::cout << msg << std::endl; }
