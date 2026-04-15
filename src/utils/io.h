#pragma once
#include <iostream>
#include <string>

class IO {

public:
  /* Gets string input from user
   * @return std::string value  the input of the user
   */
  static std::string getString();

  /* Gets integer input from user
   * @return int value  the input of the user, -1 if invalid
   */
  static int getInt();

  /* Gets float input from user
   * @return float value  the input of the user, -1 if invalid
   */
  static float getFloat();

  /* Gets double input from user
   * @return double value  the input of the user, -1 if invalid
   */
  static double getDouble();

  /* Prints data to the user
   * @param msg the message of the user
   */
  static void print(std::string msg);
};
