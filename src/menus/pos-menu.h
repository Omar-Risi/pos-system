#pragma once
#include "../utils/menu.h"
#include <vector>
#include "../models/product.h"

class PosMenu : public Menu {
    // calculates the total price of the items in the cart
    int calculateTotal(std::vector<Product*>& cart) ;
    public:
    // Constructs the POS Menu
    PosMenu();
};

