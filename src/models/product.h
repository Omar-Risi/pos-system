#pragma once

#include <string>

#include "utils/data.h"

class Product : public Data {
public:
  std::string sku;
  std::string name;
  double price;
  int stock;

  /* Creates a product model
   * @param sku product sku value
   * @param name product name
   * @param price product unit price
   * @param stock available stock count
   */
  Product(std::string sku, std::string name, double price, int stock);

  /* Displays product information
   * @return void
   */
  void display() const override;
};
