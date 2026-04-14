#include "input.h"
#include <iostream>
#include <limits>

// returns a string for user input
std::string Input::getString() {
  std::string result;
  std::cout << "> ";
  std::cin >> result;

  return result;
}

// get int input from user returns -1 if error
int Input::getInt() {
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

// get int input from user returns -1 if error
float Input::getFloat() {
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

double Input::getDouble() {
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
