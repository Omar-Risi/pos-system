#include "menu.h"
#include <functional>
#include <string>

Option::Option(std::string _title, std::function<void()> _callback)
    : title(_title), callback(_callback) {}

void Option::execute() { callback(); }

std::string Option::getTitle() { return title; }
