#pragma once

#include <string>

#include "../utils/data.h"

class Product : public Data {
public:
  std::string sku;
  std::string name;
  int price;
  int stock;

  /* Creates a product model
   * @param sku product sku value
   * @param name product name
   * @param price product unit price
   * @param stock available stock count
   */
  Product(std::string sku, std::string name, int price, int stock);

  /* Returns the price as a string
   * @return std::string price
   */
  std::string getPrice() const;

  /* Displays product information
   * @return void
   */
  void display() const override;

  // Stores the product to db
  void store();

  /*  Adds to current stock
   *  @param  quantity how much stock increases
   */
  void restock(int quantity);

  /*  takes from current stock
   *  @param  quantity how much stock decrease
   */
  void withdraw(int quantity);
};
