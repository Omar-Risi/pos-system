#include "login-menu.h"
#include "../utils/io.h"

bool LoginMenu::show() {
    IO::print("Enter username: ");

    std::string userName = IO::getString();

    IO::print("Enter password: ");

    std::string password = IO::getString();

};