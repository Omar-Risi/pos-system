#include "product.h"
#include "../utils/io.h"
#include "../utils/service.h"
#include <iomanip>
#include <sstream>
#include <string>

Product::Product(std::string sku, std::string name, int price, int stock)
    : sku(sku), name(name), price(price), stock(stock) {}

std::string Product::getPrice() const {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3) << (price / 1000.0);
  return ss.str();
}

void Product::display() const {
  IO::print(name);
  IO::print("price: " + getPrice());
  IO::print("stock: " + std::to_string(stock));
}

void Product::store() {
  Database *db = Service::getDatabase();
  if (db != nullptr) {
    db->add(sku, this);
    IO::print("Stored successfuly!");
  } else
    IO::print("Error: no databaase instance");
}

void Product::restock(int quantity) {}

void Product::withdraw(int quantity) {}
