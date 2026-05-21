#pragma once
#include "../utils/data.h"
#include "../utils/io.h"
#include "../utils/menu.h"

class InventoryMenu : public Menu {
  Table *products_table = nullptr;
  Table *stats_table = nullptr;

public:
  // Constructor for Inventory Menu
  InventoryMenu();
};
