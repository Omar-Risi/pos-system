#include "product.h"
#include "../utils/io.h"
#include "../utils/service.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

// TODO: call set columns of table

Product::Product(std::string sku, std::string name, int price, int stock)
    : sku(sku), name(name), price(price), stock(stock) {}

const std::string &Product::getSku() const { return sku; }

void Product::setSku(const std::string &value) { sku = value; }

const std::string &Product::getName() const { return name; }

void Product::setName(const std::string &value) { name = value; }

int Product::getPriceValue() const { return price; }

void Product::setPriceValue(int value) { price = value; }

int Product::getStock() const { return stock; }

void Product::setStock(int value) { stock = value; }

std::string Product::getPrice() const {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3) << (price / 1000.0);
  return ss.str();
}

int Product::getTotalPrice() const { return price * stock; }

int operator+(int total, const Product &product) {
  return total + product.getTotalPrice();
}

int operator+(const Product &product, int total) {
  return product.getTotalPrice() + total;
}

void Product::display() const {
  IO::print(sku + " | " + name + " | " + getPrice() + " | " +
            std::to_string(stock));
}

std::vector<std::string> Product::toCsvRow() const {
  return {sku, name, std::to_string(price), std::to_string(stock)};
}

void Product::store() {
  Database *db = Service::getDatabase();
  if (db != nullptr) {
    db->get("products")->add(sku, this);
    IO::print("Stored successfuly!");
  } else
    IO::print("Error: no databaase instance");
}

void Product::restock(int quantity) { stock += quantity; }

void Product::withdraw(int quantity) {
  if (stock - quantity == 0)
    stock = 0;
  else
    stock -= quantity;
}
