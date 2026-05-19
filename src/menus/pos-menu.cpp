#include "pos-menu.h"
#include "../utils/io.h"
#include <vector>
#include <string>
#include "../utils/service.h"
#include "../utils/data.h"
#include "../models/product.h"

int PosMenu::calculateTotal(std::vector<Product*>& cart) {
    int total = 0;
    for (const auto& item : cart) {
        total += item->price * item->stock; // stock is used as quantity in cart
    }
    return total;
}

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
    addOption("Edit Cart", [productsTable, &cart]() {
        Menu cartMenu = Menu("Cart");
        for (const auto& item : cart) {
            cartMenu.addOption("SKU: " + item->sku + " | " + item->name + " | $" + std::to_string(item->price) + " | Qty: " + std::to_string(item->stock), [item]() {
                Menu itemMenu = Menu("Edit Item");
                itemMenu.addOption("change quantity", [item]() {
                    int newQuantity = IO::getInt("Enter new quantity:");
                    if (newQuantity < 0) {
                        IO::print("Invalid quantity");
                        return;
                    }
                    item->stock = newQuantity;
                });
                itemMenu.addOption("remove from cart", [item]() {
                    item->stock = 0;
                });
                itemMenu.open();
            });
        }
        cartMenu.open();
    });
    addOption("Checkout", [productsTable, &cart, this]() {
        int total = calculateTotal(cart);
        IO::print("Total: $" + std::to_string(total));
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




