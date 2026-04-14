#include "menu.h"
#include <iostream>

Menu::Menu() { title = "Main Menu"; }

void Menu::displayMenu() const {
  std::cout << "--- " << title << " ---" << std::endl;
  std::cout << "1. Option One\n";
  std::cout << "2. Option Two\n";
}
