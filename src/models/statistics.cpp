#include <iostream>
#include "statistics.h"
#include "../utils/data.h"
#include "../utils/io.h" 

Statistics::Statistics(std::string const title, int numberOfSales) : title(title), numberOfSales(numberOfSales) {}

Statistics::~Statistics() {
}

void Statistics::display() const {

    IO::print(title);
    IO::print(numberOfSales);

}