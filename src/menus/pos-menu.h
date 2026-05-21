#pragma once
#include "../utils/menu.h"
#include <vector>
#include "../models/product.h"

class Table;

class PosMenu : public Menu {
    Table *products_table = nullptr;
    Table *stats_table = nullptr;
    std::vector<Product *> cart;

    // Calculates the total price of the items in the cart
    int calculateTotal(const std::vector<Product *> &cart) const;

public:
    // Constructs the POS Menu
    PosMenu();
};

