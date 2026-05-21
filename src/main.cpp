#include "menus/login-menu.h"
#include "menus/welcome-menu.h"
#include "models/product.h"
#include "models/statistics.h"
#include "utils/data.h"
#include "utils/service.h"
#include "utils/storage.h"
#include <exception>
#include <string>

using namespace std;
int main() {

  Database db;
  Service::registerDatabase(&db);

  Table *productsTable = new Table();
  productsTable->setColumns({"sku", "name", "price", "stock"});
  productsTable->setRowFactory(
      [](const std::unordered_map<std::string, std::string> &row) -> Record * {
        auto sku_it = row.find("sku");
        auto name_it = row.find("name");
        auto price_it = row.find("price");
        auto stock_it = row.find("stock");
        if (sku_it == row.end() || name_it == row.end() ||
            price_it == row.end() || stock_it == row.end()) {
          return nullptr;
        }

        try {
          int price = std::stoi(price_it->second);
          int stock = std::stoi(stock_it->second);
          return new Product(sku_it->second, name_it->second, price, stock);
        } catch (const std::exception &) {
          return nullptr;
        }
      });
  db.add("products", productsTable);

  Table *statsTable = new Table();
  statsTable->setColumns({"key", "title", "value"});
  statsTable->setRowFactory(
      [](const std::unordered_map<std::string, std::string> &row) -> Record * {
        auto key_it = row.find("key");
        auto title_it = row.find("title");
        auto value_it = row.find("value");
        if (key_it == row.end() || title_it == row.end() ||
            value_it == row.end()) {
          return nullptr;
        }

        try {
          int value = std::stoi(value_it->second);
          return new Statistics(key_it->second, title_it->second, value);
        } catch (const std::exception &) {
          return nullptr;
        }
      });
  statsTable->add("gross_revenue",
                  new Statistics("gross_revenue", "Gross revenue", 0));
  statsTable->add("total_products",
                  new Statistics("total_products", "Total products", 0));
  statsTable->add(
      "transactions",
      new Statistics("transactions", "Number of transactions", 0));
  db.add("statistics", statsTable);

  Storage::loadAll();

  LoginMenu loginMenu;

  bool isLoggedIn = loginMenu.open("admin", "admin123");

  if (isLoggedIn) {
    WelcomeMenu welcomeMenu;
    welcomeMenu.open();
  }
  Storage::saveAll();
  return 0;
}
