#include "login-menu.h"
#include "../utils/io.h"
#include <string>

bool LoginMenu::open(std::string user, std::string pass) {

  for (int i = 3; i > 0; i--) {

    std::string userName = IO::getString("Enter username");

    std::string password = IO::getString("Enter password");

    if (userName == user && password == pass) {
      return true;
    } else {
      continue;
    }
  }

  return false;
}
