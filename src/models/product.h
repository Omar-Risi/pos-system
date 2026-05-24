#pragma once

#include <string>

#include "../utils/data.h"

class Product : public Record {
private:
  std::string sku;
  std::string name;
  int price;
  int stock;

public:

  /* Creates a product model
   * @param sku product sku value
   * @param name product name
   * @param price product unit price
   * @param stock available stock count
   */
  Product(std::string sku, std::string name, int price, int stock);

  const std::string &getSku() const;
  void setSku(const std::string &value);

  const std::string &getName() const;
  void setName(const std::string &value);

  int getPriceValue() const;
  void setPriceValue(int value);

  int getStock() const;
  void setStock(int value);

  /* Returns the price as a string
   * @return std::string price
   */
  std::string getPrice() const;

  int getTotalPrice() const;

  friend int operator+(int total, const Product &product);
  friend int operator+(const Product &product, int total);

  /* Displays product information
   * @return void
   */
  void display() const override;

  /* Converts the product into a CSV row
   * @return vector<string> row data in CSV column order
   */
  std::vector<std::string> toCsvRow() const override;

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
