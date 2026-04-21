#pragma once
#include <iostream>
#include <string>

class IO {

public:
  /* Gets string input from user
   * @param message input message, if not provided uses ">"
   * @return std::string value  the input of the user
   */
  static std::string getString(std::string msg);

  /* Gets integer input from user
   * @param message input message, if not provided uses ">"
   * @return int value  the input of the user, -1 if invalid
   */
  static int getInt(std::string msg);

  /* Gets float input from user
   * @param message input message, if not provided uses ">"
   * @return float value  the input of the user, -1 if invalid
   */
  static float getFloat(std::string msg);

  /* Gets double input from user
   * @param message input message, if not provided uses ">"
   * @return double value  the input of the user, -1 if invalid
   */
  static double getDouble(std::string msg);

  /* Prints data to the user
   * @param msg the message of the user
   */
  static void print(std::string msg);
};
