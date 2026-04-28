#include "pos-menu.h"
#include "../utils/io.h"

PosMenu::PosMenu() : Menu("POS Menu") {
    addOption("Add Product", []() {
        std::string sku = IO::getString("Enter SKU:");
        int quantity = IO::getInt("Enter quantity:");
    });
    addOption("Edit Cart", []() {
        IO::print("1. SKU: 1234 | Coffee | $2.50 | Qty: 2");
        IO::print("2. SKU: 1234 | Coffee | $2.50 | Qty: 2");
        IO::print("3. SKU: 1234 | Coffee | $2.50 | Qty: 2");
        IO::print("4. SKU: 1234 | Coffee | $2.50 | Qty: 2");
    });
    addOption("Checkout", []() {
        IO::print("Total: ");
        std::string paymentMethod;

        Menu paymentMenu = Menu("Select Payment Method");
        paymentMenu.addOption("Cash", [&paymentMethod]() {
            paymentMethod = "Cash";
        });
        paymentMenu.addOption("Card", [&paymentMethod]() {
            paymentMethod = "Card";
        });

    });


}




