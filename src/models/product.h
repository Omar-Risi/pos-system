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

  /* Returns the product SKU
   * @return const std::string& sku
   */
  const std::string &getSku() const;

  /* Sets the product SKU
   * @param value new sku value
   * @return void
   */
  void setSku(const std::string &value);

  /* Returns the product name
   * @return const std::string& name
   */
  const std::string &getName() const;

  /* Sets the product name
   * @param value new name value
   * @return void
   */
  void setName(const std::string &value);

  /* Returns the product price as integer value
   * @return int price value
   */
  int getPriceValue() const;

  /* Sets the product price value
   * @param value new price
   * @return void
   */
  void setPriceValue(int value);

  /* Returns current stock count
   * @return int stock
   */
  int getStock() const;

  /* Sets the stock count
   * @param value new stock count
   * @return void
   */
  void setStock(int value);

  /* Returns the price as a string
   * @return std::string price
   */
  std::string getPrice() const;

  /* Returns total price (price * quantity if applicable)
   * @return int total price
   */
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

  /* Stores the product to the database
   * @return void
   */
  void store();

  /*  Adds to current stock
   *  @param quantity how much stock increases
   *  @return void
   */
  void restock(int quantity);

  /*  Takes from current stock
   *  @param quantity how much stock decrease
   *  @return void
   */
  void withdraw(int quantity);
};
