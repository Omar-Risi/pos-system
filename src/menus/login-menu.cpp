#include "login-menu.h"
#include "../utils/io.h"
#include <string>


bool LoginMenu::show() {

    std::string userName = IO::getString("Enter username: ");

    std::string password = IO::getString("Enter password: ");

};