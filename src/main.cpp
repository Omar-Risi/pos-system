#include "utils/io.h"
#include "utils/menu.h"
#include <iostream>

using namespace std;
int main() {

  Menu welcomeMenu = Menu("Welcome Menu");
  welcomeMenu.addOption(Option("option 1", []() { IO::print("Option 1"); }));
  welcomeMenu.open();

  return 0;
}
