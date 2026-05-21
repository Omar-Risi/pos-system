#include "statistics-menu.h"
#include "../utils/io.h"

StatisticsMenu::StatisticsMenu()
    : Menu("=== Statistics ===\nWhat do you want to know?") {

  addOption("gross revenue", []() { IO::print("Gross revenue: 0"); });

  addOption("total products", []() { IO::print("Total products: 0"); });

  addOption("number of transactions",
            []() { IO::print("Number of transactions: 0"); });
}
