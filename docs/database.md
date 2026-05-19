
# Database quick guide

This project stores data in a simple in-memory database built from three types:

## Architecture

```
Database
  ├── Table ("products")
  │    ├── Record: Product (SKU-001)
  │    ├── Record: Product (SKU-002)
  │    └── ...
  ├── Table ("orders")
  │    ├── Record: Order (ORD-001)
  │    ├── Record: Order (ORD-002)
  │    └── ...
  └── ...
```

**Three-tier structure:**
1. **Database**: Owns multiple `Table*` items keyed by string (e.g., "products", "orders")
2. **Table**: Owns multiple `Record*` items keyed by string (e.g., product SKU, order ID)
3. **Record** (Model): Abstract base class—your domain models inherit from it (e.g., `Product`, `Order`)

**Ownership matters:** `Table` deletes all stored `Record*` and `Database` deletes all stored `Table*` in their destructors and when you remove items.

## 1) Create a record type

Create a class that inherits `Record` and implements `display()`.

```cpp
#include "utils/data.h"
#include <string>

class Product : public Record {
public:
	std::string sku;
	std::string name;

	Product(const std::string &sku, const std::string &name) : sku(sku), name(name) {}

	void display() const override {
		// Example display
		std::cout << sku << " - " << name << std::endl;
	}
};
```

## 2) Create a database and add a table

```cpp
#include "utils/data.h"

Database db;
db.add("products", new Table());
```

You can follow the same pattern for other tables, e.g. `db.add("orders", new Table());`.

## 3) Store (insert) a record

```cpp
Table *products = db.get("products");
if (products != nullptr) {
	products->add("SKU-001", new Product("SKU-001", "Coffee"));
}
```

## 4) Fetch and update a record

Fetch returns a `Record*`. Cast it to your concrete type, then update fields.

```cpp
Table *products = db.get("products");
if (products != nullptr) {
	Record *raw = products->get("SKU-001");
	if (raw != nullptr) {
		Product *p = dynamic_cast<Product *>(raw);
		if (p != nullptr) {
			p->name = "Iced Coffee"; // update in place
		}
	}
}
```

Because the table stores pointers, updating fields on the retrieved object updates the stored record.

## 5) Remove a record

```cpp
Table *products = db.get("products");
if (products != nullptr) {
	products->remove("SKU-001"); // deletes the record and removes the key
}
```

## 6) Remove a table

```cpp
db.remove("products"); // deletes the table and all records in it
```

## Complete Example: Using Database, Table, and Model Together

```cpp
#include "utils/data.h"
#include <iostream>

// 1. Define your model (Record subclass)
class Product : public Record {
public:
	std::string sku;
	std::string name;
	double price;

	Product(const std::string &sku, const std::string &name, double price)
		: sku(sku), name(name), price(price) {}

	void display() const override {
		std::cout << "[" << sku << "] " << name << " - $" << price << std::endl;
	}
};

// 2. Set up the database and table
int main() {
	// Create database
	Database db;
	
	// Add a table for products
	db.add("products", new Table());

	// 3. Insert records into the table
	Table *products = db.get("products");
	if (products != nullptr) {
		products->add("SKU-001", new Product("SKU-001", "Coffee", 3.99));
		products->add("SKU-002", new Product("SKU-002", "Tea", 2.99));
		products->add("SKU-003", new Product("SKU-003", "Juice", 4.49));
	}

	// 4. Iterate through all records in a table
	std::cout << "All products:\n";
	if (products != nullptr) {
		products->display();
	}

	// 5. Fetch and update a record
	std::cout << "\nUpdating coffee price...\n";
	if (products != nullptr) {
		Record *raw = products->get("SKU-001");
		if (raw != nullptr) {
			Product *p = dynamic_cast<Product *>(raw);
			if (p != nullptr) {
				p->price = 4.29; // Update in place
			}
		}
	}

	// 6. Display updated record
	std::cout << "Updated products:\n";
	if (products != nullptr) {
		products->display();
	}

	// 7. Remove a specific record
	std::cout << "\nRemoving SKU-002...\n";
	if (products != nullptr) {
		products->remove("SKU-002");
	}

	// 8. Remove an entire table (cascades delete all records)
	std::cout << "Removing products table...\n";
	db.remove("products");

	// Database destructor cleans up remaining tables
	return 0;
}
```

## Notes

- `get()` returns `nullptr` if the key is missing.
- `remove()` deletes the stored pointer; do not use it after removal.
- If you add a record with an existing key, the old pointer is overwritten; delete it first if you own it elsewhere.
- The `display()` method on `Table` calls `display()` on all its records in sequence.
