#include "menus/inventory-menu.h"
#include "utils/service.h"
#include "utils/data.h"
#include "models/product.h"
// Must add actual interactions to each option, and link it to the database.
InventoryMenu::InventoryMenu() : Menu("Inventory Manager") {
    Table* products_table = Service::getDatabase()->get("products");
    addOption("List Products", [products_table](){
        Record* record = products_table->get("");
        if (record != nullptr) {
            record->display();
        }
    });
    addOption("Add Product", [&products_table](){
        
        std::string name = IO::getString("Enter Product Name: ");
        std::string sku = IO::getInt("Enter SKU: ");
        int stock = IO::getInt("Enter Quantity: ");
        int price = IO::getInt("Enter Price: ");
        Record* product = new Product(sku, name, price, stock); 
        products_table->add(sku, product);
    });
    addOption("Update Product", [](){
        IO::getInt("Enter SKU to update: ");
        Menu updateMenu("\nWhat do you want to update?");
        updateMenu.addOption("Name", [](){IO::getString("Enter new name: ");});
        updateMenu.addOption("Quantity", [](){IO::getInt("Enter new quantity: ");});
        updateMenu.addOption("Price", [](){IO::getString("Enter new price:");});
        updateMenu.open();
    });
    addOption("Delete Product", [](){IO::getInt("Enter SKU to delete: ");
        Menu confirmMenu("\n Are you sure you want to delete: \n");
        confirmMenu.addOption("Yes", [](){IO::print("Product deleted successfully.");});
        confirmMenu.addOption("No", [](){IO::print("Cancelled product deletion");});
        confirmMenu.open();
});
}

