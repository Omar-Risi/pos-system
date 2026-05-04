
# Database quick guide

This project stores data in a simple in-memory database built from three types:

- `Record`: abstract base class for items you store.
- `Table`: owns `Record*` items keyed by string.
- `Database`: owns `Table*` items keyed by string.

Ownership matters: `Table` deletes all stored `Record*` and `Database` deletes all stored `Table*` in their destructors and when you remove items.

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

## Notes

- `get()` returns `nullptr` if the key is missing.
- `remove()` deletes the stored pointer; do not use it after removal.
- If you add a record with an existing key, the old pointer is overwritten; delete it first if you own it elsewhere.
