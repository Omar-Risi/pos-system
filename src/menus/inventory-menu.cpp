#include "menus/inventory-menu.h"
#include "utils/service.h"
#include "utils/data.h"
#include "models/product.h"
// Must add actual interactions to each option, and link it to the database.
InventoryMenu::InventoryMenu() : Menu("Inventory Manager") {
    Table* products_table = Service::getDatabase()->get("products");
    addOption("List Products", [products_table](){
        Record* record = products_table->getAll();
        if (record != nullptr) {
            record->display();
        }
    });
    addOption("Add Product", [&products_table](){
        
        std::string name = IO::getString("Enter Product Name: ");
        std::string sku = IO::getString("Enter SKU: ");
        int stock = IO::getInt("Enter Quantity: ");
        int price = IO::getInt("Enter Price: ");
        Record* product = new Product(sku, name, price, stock); 
        products_table->add(sku, product);
    });
    addOption("Update Product", [&products_table](){
        std::string sku = IO::getString("Enter SKU to update: ");
        Record* p = products_table->get(sku);
        Product* product = (Product*)p;
        Menu updateMenu("\nWhat do you want to update?");
        updateMenu.addOption("Name", [product](){product->name = IO::getString("Enter new name: ");});
        updateMenu.addOption("Quantity", [product](){product->stock = IO::getInt("Enter new quantity: ");});
        updateMenu.addOption("Price", [product](){product->price = IO::getInt("Enter new price:");});
        updateMenu.open();
    });
    addOption("Delete Product", [&products_table](){std::string sku = IO::getString("Enter SKU to delete: ");
        Menu confirmMenu("\n Are you sure you want to delete: \n");
        confirmMenu.addOption("Yes", [products_table, sku](){products_table->remove(sku); IO::print("Product deleted successfully.");});
        confirmMenu.addOption("No", [](){IO::print("Cancelled product deletion");});
        confirmMenu.open();
});
}

