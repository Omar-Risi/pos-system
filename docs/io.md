# IO Class Guide

The `IO` class is a static utility for basic console input/output in this POS system.
It centralizes user prompts, input parsing, and simple output formatting so other parts
of the app can stay focused on business logic.

## Location

- Header: `src/utils/io.h`
- Implementation: `src/utils/io.cpp`

## What It Provides

All methods are `static`, so you call them directly on `IO`.

- `std::string IO::getString(std::string msg)`
- `int IO::getInt(std::string msg)`
- `float IO::getFloat(std::string msg)`
- `double IO::getDouble(std::string msg)`
- `void IO::print(std::string msg)`

## Behavior Notes

- Each input method accepts a prompt message via the `msg` parameter.
- Per the header comments, if no message is provided, the prompt falls back to `>`.
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

  std::string name = IO::getString("Enter product name:");

  double price = IO::getDouble("Enter price:");
  if (price == -1) {
    IO::print("Invalid price.");
    return;
  }

  int quantity = IO::getInt("Enter quantity:");
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
