#include "menus/inventory-menu.h"

InventoryMenu::InventoryMenu() : Menu("Inventory Manager") {
    addOption("List Products", [](){
        IO::print("Name: Coffee | SKU: 1234 | Quantity: 10");
        IO::print("Name: Bagel | SKU: 5678 | Quantity: 5");
        IO::print("Name: Croissant | SKU: 9012 | Quantity: 8");
    });
    addOption("Add Product", [](){
        IO::getString("Enter Product Name: ");
        IO::getInt("Enter SKU: ");
        IO::getInt("Enter Quantity: ");
        IO::getInt("Enter Price: ");
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