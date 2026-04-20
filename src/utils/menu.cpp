#include "menu.h"
#include "io.h"
#include <functional>
#include <string>

Option::Option(std::string _title, std::function<void()> _callback)
    : title(_title), callback(_callback) {}

void Option::execute() { callback(); }

std::string Option::getTitle() { return title; }

void Menu::addOption(std::string _title, std::function<void()> _callback) {
  options.push_back(Option(_title, _callback));
}

void Menu::display() {

  // make menu readable
  IO::print("");

  IO::print(title);

  for (int i = 0; i < options.size(); i++) {
    IO::print(std::to_string(i + 1) + ". " + options[i].getTitle());
  }

  IO::print(std::to_string(options.size() + 1) + ". exit");
}

void Menu::open() {
  while (true) {
    display();
    int input = IO::getInt();

    if (input == -1 || input < 1 || input > options.size() + 1)
      continue; // skips on invalid input

    if (input == options.size() + 1)
      break;

    options[input - 1].execute();
  }
}
