#include "io.h"
#include <iostream>
#include <limits>
#include <string>

std::string IO::getString() {
  std::string result;
  std::cout << "> ";
  std::cin >> result;

  return result;
}

int IO::getInt() {
  int value;
  std::cout << "> ";
  if (!(std::cin >> value)) {
    std::cout << "Error: Input is not an integer." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return -1;
  }
  return value;
}

float IO::getFloat() {
  float value;
  std::cout << "> ";
  if (!(std::cin >> value)) {
    std::cout << "Error: Input is not a float." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return -1;
  }
  return value;
}

double IO::getDouble() {
  double value;
  std::cout << "> ";
  if (!(std::cin >> value)) {
    std::cout << "Error: Input is not a double." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return -1;
  }
  return value;
}

void IO::print(std::string msg) { std::cout << msg << std::endl; }
