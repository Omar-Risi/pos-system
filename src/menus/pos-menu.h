#pragma once
#include "../utils/menu.h"
#include <vector>
#include "../models/product.h"

class Table;

class PosMenu : public Menu {
    Table *products_table = nullptr;
    Table *stats_table = nullptr;
    std::vector<Product *> cart;

    /* Calculates the total price of the items in the cart
     * @param cart vector of product pointers
     * @return int total price
     */
    int calculateTotal(const std::vector<Product *> &cart) const;

public:
    /* Constructs the POS Menu
     * @return void
     */
    PosMenu();
};

