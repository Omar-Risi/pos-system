#include "menus/inventory-menu.h"

InventoryMenu::InventoryMenu() : Menu("Inventory Manager") {
    addOption("List Products", [](){IO::print("Name: | SKU: | Quantity:");});
    addOption("Add Product", [](){IO::print("Enter Product Name: \n Enter SKU: \n Enter Quantity: \n Enter Price: ");});
    addOption("Update Product", [](){IO::print("Enter SKU to update: \n Enter new name: \n Enter new quantity: \n Enter new price: ");});
    addOption("Delete Product", [](){IO::print("Enter SKU to delete: ");
        Menu Confirm("\n Are you sure you want to delete: \n");
        Confirm.addOption("Yes", [](){IO::print("Product deleted successfully.");});
        Confirm.addOption("No", [](){IO::print("Cancelled product deletion");});
        Confirm.open();
});
}