#pragma once
#include <string>

class Menu {
public:
  Menu();
  void displayMenu() const;

private:
  std::string title;
};
