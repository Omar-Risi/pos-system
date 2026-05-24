#include "inventory-menu.h"
#include "../models/product.h"
#include "../models/statistics.h"
#include "../utils/data.h"
#include "../utils/service.h"
#include "../utils/storage.h"

InventoryMenu::InventoryMenu() : Menu("Inventory Manager") {
  Database *db = Service::getDatabase();
  products_table = db ? db->get("products") : nullptr;
  stats_table = db ? db->get("statistics") : nullptr;

  addOption("List Products", [this]() {
    if (!products_table) {
      IO::print("Products table not initialized");
      return;
    }
    std::vector<Record *> records = products_table->getAll();
    if (records.empty()) {
      IO::print("No products found");
      return;
    }
    for (Record *record : records) {
      if (record != nullptr) {
        record->display();
      }
    }
  });
  addOption("Add Product", [this]() {
    if (!products_table) {
      IO::print("Products table not initialized");
      return;
    }
    std::string name = IO::getString("Enter Product Name");
    std::string sku = IO::getString("Enter SKU");
    int stock = IO::getInt("Enter Quantity");
    int price = IO::getInt("Enter Price");

    bool existed = products_table->get(sku) != nullptr;
    Record *product = new Product(sku, name, price, stock);
    products_table->add(sku, product);

    if (!existed && stats_table) {
      Statistics *total =
          dynamic_cast<Statistics *>(stats_table->get("total_products"));
      if (total) {
        total->setValue(total->getValue() + 1);
      }
    }
    Storage::saveTemp();
  });
  addOption("Update Product", [this]() {
    if (!products_table) {
      IO::print("Products table not initialized");
      return;
    }
    std::string sku = IO::getString("Enter SKU to update");
    Record *p = products_table->get(sku);
    Product *product = dynamic_cast<Product *>(p);
    if (!product) {
      IO::print("Product not found");
      return;
    }
    Menu updateMenu("\nWhat do you want to update?");
    updateMenu.addOption("Name", [product]() {
      product->setName(IO::getString("Enter new name"));
    });
    updateMenu.addOption("Quantity", [product]() {
      product->setStock(IO::getInt("Enter new quantity"));
    });
    updateMenu.addOption("Price", [product]() {
      product->setPriceValue(IO::getInt("Enter new price"));
    });
    updateMenu.open();
    Storage::saveTemp();
  });
  addOption("Delete Product", [this]() {
    if (!products_table) {
      IO::print("Products table not initialized");
      return;
    }
    std::string sku = IO::getString("Enter SKU to delete");
    if (!products_table->get(sku)) {
      IO::print("Product not found");
      return;
    }
    if (!Menu::confirm("Are you sure you want to delete?")) {
      IO::print("Cancelled product deletion");
      return;
    }
    products_table->remove(sku);
    if (stats_table) {
      Statistics *total =
          dynamic_cast<Statistics *>(stats_table->get("total_products"));
      if (total && total->getValue() > 0) {
        total->setValue(total->getValue() - 1);
      }
    }
    IO::print("Product deleted successfully.");
    Storage::saveTemp();
  });
}
