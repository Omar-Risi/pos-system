#include <iostream>
#include "statistics.h"
#include "../utils/data.h"
#include "../utils/io.h" 

Statistics::Statistics(std::string key, std::string title, int numberOfSales)
    : key(key), title(title), value(numberOfSales) {}

Statistics::~Statistics() {
}

const std::string &Statistics::getKey() const { return key; }

void Statistics::setKey(const std::string &value) { key = value; }

const std::string &Statistics::getTitle() const { return title; }

void Statistics::setTitle(const std::string &value) { title = value; }

int Statistics::getValue() const { return value; }

void Statistics::setValue(int value) { this->value = value; }

void Statistics::display() const {

    IO::print(title);
    IO::print(value);

}

std::vector<std::string> Statistics::toCsvRow() const {
    return {key, title, std::to_string(value)};
}