#include "models/product.h"

#include <iomanip>
#include <iostream>

Product::Product(std::string sku, std::string name, double price, int stock)
    : sku(sku), name(name), price(price), stock(stock) {}

void Product::display() const {
  std::cout << name << " - $" << std::fixed << std::setprecision(2) << price
            << " (" << stock << " in stock)\n";
}
