#pragma once
#include <iostream>
#include <string>

class LoginMenu {

public:
  /* Show the login menu
   *  @param user username
   *  @param pass user password
   */
  bool open(std::string user, std::string pass);
};
