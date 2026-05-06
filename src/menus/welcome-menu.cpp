#include "welcome-menu.h"
#include "inventory-menu.h"
#include "pos-menu.h"
#include "../utils/io.h"

WelcomeMenu::WelcomeMenu() : Menu("Welcome to the POS System!") {
  addOption("Go to POS Menu", []() {
    PosMenu posMenu;
    posMenu.open();
  });
  addOption("Go to Inventory Menu", []() {
    InventoryMenu inventoryMenu;
    inventoryMenu.open();
  });
  addOption("Open statistics menu", []() {
    IO::print("Coming soon...");
  });
}
