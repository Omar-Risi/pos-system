#pragma once
#include <iostream>
#include <string>

class IO {

public:
  static std::string getString();
  static int getInt();
  static float getFloat();
  static double getDouble();
  static void print(std::string msg);
};
