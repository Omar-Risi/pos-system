#include "pos-menu.h"
#include "../utils/io.h"
#include <vector>
#include <string>
#include "../utils/service.h"
#include "../utils/data.h"
#include "../models/product.h"

PosMenu::PosMenu() : Menu("POS Menu") {
    Database* db = Service::getDatabase();
    Table* productsTable = db->get("products");
    std::vector<Product*> cart;

    addOption("Add Product", [productsTable, &cart]() {

        std::string sku = IO::getString("Enter SKU:");
        Product* product = dynamic_cast<Product*>(productsTable->get(sku));

        if(product == nullptr) {
            IO::print("Product not found");
            return;
        }

        int quantity = IO::getInt("Enter quantity:");
        
        if (product->stock < quantity) {
            IO::print("Not enough stock");
            return;
        }

        Product* cartItem = new Product(product->sku, product->name, product->price, quantity);
        product->withdraw(quantity);
        cart.push_back(cartItem);
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




