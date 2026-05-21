#include "statistics-menu.h"
#include "../models/statistics.h"
#include "../utils/data.h"
#include "../utils/io.h"
#include "../utils/service.h"

StatisticsMenu::StatisticsMenu()
    : Menu("=== Statistics ===\nWhat do you want to know?") {
  Database *db = Service::getDatabase();
  Table *stats_table = db ? db->get("statistics") : nullptr;
  Table *products_table = db ? db->get("products") : nullptr;

  addOption("gross revenue", [stats_table]() {
    Statistics *revenue = stats_table
                              ? dynamic_cast<Statistics *>(
                                    stats_table->get("gross_revenue"))
                              : nullptr;
    int value = revenue ? revenue->value : 0;
    IO::print("Gross revenue: " + std::to_string(value));
  });

  addOption("total products", [stats_table, products_table]() {
    Statistics *total = stats_table
                            ? dynamic_cast<Statistics *>(
                                  stats_table->get("total_products"))
                            : nullptr;
    if (total) {
      IO::print("Total products: " + std::to_string(total->value));
      return;
    }

    int count = 0;
    if (products_table) {
      count = static_cast<int>(products_table->getAll().size());
    }
    IO::print("Total products: " + std::to_string(count));
  });

  addOption("number of transactions", [stats_table]() {
    Statistics *transactions = stats_table
                                   ? dynamic_cast<Statistics *>(
                                         stats_table->get("transactions"))
                                   : nullptr;
    int value = transactions ? transactions->value : 0;
    IO::print("Number of transactions: " + std::to_string(value));
  });
}
