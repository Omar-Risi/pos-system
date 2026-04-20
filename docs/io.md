# IO Class Guide

The `IO` class is a static utility for basic console input/output in this POS system.
It centralizes user prompts, input parsing, and simple output formatting so other parts
of the app can stay focused on business logic.

## Location

- Header: `src/utils/io.h`
- Implementation: `src/utils/io.cpp`

## What It Provides

All methods are `static`, so you call them directly on `IO`.

- `std::string IO::getString()`
- `int IO::getInt()`
- `float IO::getFloat()`
- `double IO::getDouble()`
- `void IO::print(std::string msg)`

## Behavior Notes

- Each input method prints a `> ` prompt before reading.
- `getInt()`, `getFloat()`, and `getDouble()` return `-1` if parsing fails.
- On invalid numeric input, the method clears the stream error state and discards the
  invalid line, so the next read can continue safely.
- `getString()` reads a single token (space-separated), not a full line.
- `print()` writes a line to `std::cout`.

## Example

```cpp
#include "src/utils/io.h"

void addProductFlow() {
  IO::print("Add Product");

  IO::print("Enter product name:");
  std::string name = IO::getString();

  IO::print("Enter price:");
  double price = IO::getDouble();
  if (price == -1) {
    IO::print("Invalid price.");
    return;
  }

  IO::print("Enter quantity:");
  int quantity = IO::getInt();
  if (quantity == -1) {
    IO::print("Invalid quantity.");
    return;
  }

  IO::print("Saved: " + name);
}
```

## Tips For Developers

- Always validate numeric results against `-1` before using them.
- If product names can contain spaces, consider extending `getString()` to use
  `std::getline` in future updates.
