#include <iostream>
#include "statistics.h"
#include "../utils/data.h"
#include "../utils/io.h" 

Statistics::Statistics(std::string title, int numberOfSales) : title(title), numberOfSales(numberOfSales) {}

void Statistics::display() const {

    IO::print(Statistics::title);
    IO::print(Statistics::numberOfSales);

}