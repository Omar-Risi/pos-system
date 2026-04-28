#include "statistics_menu.h"
#include "../utils/menu.h"
#include "../utils/io.h"

void showGrossRevenue() {
  IO::print("Gross revenue: 0");
}

void showTotalProducts() {
  IO::print("Total products: 0");
}

void showTransactions() {
  IO::print("Number of transactions: 0");
}

void StatisticsMenu::open() {
  Menu menu("=== Statistics === What do you want to know?");

  menu.addOption("gross revenue", showGrossRevenue);
  menu.addOption("total products", showTotalProducts);
  menu.addOption("number of transactions", showTransactions);

  menu.open();
}
