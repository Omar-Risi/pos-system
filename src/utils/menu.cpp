#include "menu.h"
#include "io.h"
#include <functional>
#include <string>

Option::Option(std::string _title, std::function<void()> _callback)
    : title(_title), callback(_callback) {}

void Option::execute() { callback(); }

std::string Option::getTitle() { return title; }

void Menu::addOption(Option option) { options.push_back(option); }

void Menu::display() {
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

    if (input == -1 || input < 0 || input > options.size())
      continue; // skips on invalid input

    if (input == options.size())
      break;

    options[input].execute();
  }
}
