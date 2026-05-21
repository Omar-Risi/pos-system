#include <iostream>
#include "statistics.h"
#include "../utils/data.h"
#include "../utils/io.h" 

Statistics::Statistics(std::string key, std::string title, int numberOfSales)
    : key(key), title(title), value(numberOfSales) {}

Statistics::~Statistics() {
}

void Statistics::display() const {

    IO::print(title);
    IO::print(value);

}

std::vector<std::string> Statistics::toCsvRow() const {
    return {key, title, std::to_string(value)};
}