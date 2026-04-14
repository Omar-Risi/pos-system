#include "io.h"
#include <iostream>
#include <limits>
#include <string>

// returns a string for user input
std::string IO::getString() {
  std::string result;
  std::cout << "> ";
  std::cin >> result;

  return result;
}

// get int input from user returns -1 if error
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

// get float input from user returns -1 if error
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

// get double input from user returns -1 if error
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

// print data for user
void IO::print(std::string msg) { std::cout << msg << std::endl; }
