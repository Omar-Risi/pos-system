# Menu and Option Class Guide

The `Menu` and `Option` classes provide a simple callback-driven console menu.
You define options with titles and actions, add them to a `Menu`, then call `open()`
to run an interactive loop.

## Location

- Header: `src/utils/menu.h`
- Implementation: `src/utils/menu.cpp`

## Main Concepts

### Option

`Option` represents one selectable menu item.

- Constructor:
  - `Option(std::string title, std::function<void()> callback)`
- Methods:
  - `void execute()` runs the callback
  - `std::string getTitle()` returns display text

### Menu

`Menu` owns a list of `Option` items and handles rendering/input.

- Constructor:
  - `Menu(std::string title)`
- Methods:
  - `void addOption(std::string title, std::function<void()> callback)`
  - `void display()`
  - `void open()`

## Behavior Notes

- `display()` prints:
  - a blank line
  - menu title
  - numbered options starting at `1`
  - one extra auto-generated option: `N+1. exit`
- `open()` runs in a loop:
  - reads input using `IO::getInt()`
  - ignores invalid values and out-of-range choices
  - exits when the user selects the generated `exit` option
  - executes the selected option callback otherwise

## Example

```cpp
#include "src/utils/menu.h"
#include "src/utils/io.h"

void launchMainMenu() {
  Menu mainMenu("Main Menu");

  mainMenu.addOption("List Products", []() {
    IO::print("Listing products...");
    // call product listing logic here
  });

  mainMenu.addOption("Add Product", []() {
    IO::print("Opening add product flow...");
    // call add product logic here
  });

  mainMenu.addOption("Checkout", []() {
    IO::print("Opening checkout...");
    // call checkout logic here
  });

  mainMenu.open();
}
```

## Tips For Developers

- Keep each option callback focused; call service/domain functions from it.
- If callbacks become large, move logic into named functions and call those from the lambda.
- Because `open()` blocks in a loop, run it from your top-level flow (like `main`).
