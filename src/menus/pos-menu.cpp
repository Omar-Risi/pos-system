#include "pos-menu.h"
#include "../utils/io.h"
#include <vector>
#include <string>
#include <stdexcept>
#include "../utils/service.h"
#include "../utils/data.h"
#include "../models/product.h"
#include "../models/statistics.h"
#include "../utils/storage.h"

int PosMenu::calculateTotal(const std::vector<Product *> &cart) const {
    int total = 0;
    for (const auto &item : cart) {
        total = total + *item; // stock is used as quantity in cart
    }
    return total;
}

PosMenu::PosMenu() : Menu("POS Menu") {
    Database *db = Service::getDatabase();
    products_table = db ? db->get("products") : nullptr;
    stats_table = db ? db->get("statistics") : nullptr;

    addOption("Add Product", [this]() {
        if (!products_table) {
            IO::print("Products table not initialized");
            return;
        }

        std::string sku = IO::getString("Enter SKU");
        Product *product = dynamic_cast<Product *>(products_table->get(sku));

        if (product == nullptr) {
            IO::print("Product not found");
            return;
        }

        int quantity = IO::getInt("Enter quantity");
        if (quantity <= 0) {
            IO::print("Invalid quantity");
            return;
        }

        if (product->getStock() < quantity) {
            IO::print("Not enough stock");
            return;
        }

        Product *cartItem =
            new Product(product->getSku(), product->getName(), product->getPriceValue(), quantity);
        cart.push_back(cartItem);
    });
    addOption("Edit Cart", [this]() {
        if (cart.empty()) {
            IO::print("Cart is empty");
            return;
        }
        Menu cartMenu = Menu("Cart");
        for (const auto &item : cart) {
            cartMenu.addOption(
                    "SKU: " + item->getSku() + " | " + item->getName() + " | $" +
                            std::to_string(item->getPriceValue()) + " | Qty: " +
                            std::to_string(item->getStock()),
                    [item]() {
                        Menu itemMenu = Menu("Edit Item");
                        itemMenu.addOption("change quantity", [item]() {
                            int newQuantity = IO::getInt("Enter new quantity:");
                            if (newQuantity < 0) {
                                IO::print("Invalid quantity");
                                return;
                            }
                            item->setStock(newQuantity);
                        });
                        itemMenu.addOption("remove from cart", [item]() { item->setStock(0); });
                        itemMenu.open();
                    });
        }
        cartMenu.open();
    });
    addOption("Checkout", [this]() {
        if (cart.empty()) {
            IO::print("Cart is empty");
            return;
        }
        if (!products_table) {
            IO::print("Products table not initialized");
            return;
        }

        std::vector<Product *> checkoutItems;
        checkoutItems.reserve(cart.size());
        for (const auto &item : cart) {
            if (item->getStock() > 0) {
                checkoutItems.push_back(item);
            }
        }

        if (checkoutItems.empty()) {
            IO::print("Cart is empty");
            return;
        }

        try {
            for (const auto &item : checkoutItems) {
                Product *product =
                    dynamic_cast<Product *>(products_table->get(item->getSku()));
                if (!product) {
                    throw std::runtime_error("Product not found: " + item->getSku());
                }
                if (product->getStock() < item->getStock()) {
                    throw std::runtime_error("Not enough stock for: " + item->getSku());
                }
            }
        } catch (const std::exception &ex) {
            IO::print(ex.what());
            return;
        }

        int total = calculateTotal(checkoutItems);
        IO::print("Total: $" + std::to_string(total));
        std::string paymentMethod;

        Menu paymentMenu = Menu("Select Payment Method");
        paymentMenu.addOption("Cash", [&paymentMethod]() { paymentMethod = "Cash"; });
        paymentMenu.addOption("Card", [&paymentMethod]() { paymentMethod = "Card"; });
        int selection = paymentMenu.openOnce();
        if (selection == 0) {
            IO::print("Checkout cancelled");
            return;
        }

        if (!Menu::confirm("Confirm checkout?")) {
            IO::print("Checkout cancelled");
            return;
        }

        for (const auto &item : checkoutItems) {
            Product *product =
                dynamic_cast<Product *>(products_table->get(item->getSku()));
            if (product) {
                product->withdraw(item->getStock());
            }
        }

        if (stats_table) {
            Statistics *revenue =
                dynamic_cast<Statistics *>(stats_table->get("gross_revenue"));
            if (revenue) {
                revenue->setValue(revenue->getValue() + total);
            }

            Statistics *transactions =
                dynamic_cast<Statistics *>(stats_table->get("transactions"));
            if (transactions) {
                transactions->setValue(transactions->getValue() + 1);
            }
        }

        for (auto *item : cart) {
            delete item;
        }
        cart.clear();

        IO::print("Checkout complete: " + paymentMethod);
        Storage::saveTemp();
    });
}




