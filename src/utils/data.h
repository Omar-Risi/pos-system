#pragma once

#include <string>
#include <unordered_map>

// Base class for all storable types
class Data {
public:
  /* Displays this data item
   * @return void
   */
  virtual void display() const = 0; // pure virtual - every subclass must implement

  /* Virtual destructor for polymorphic cleanup
   * @return void
   */
  virtual ~Data() = default;
};

class Database {
  std::unordered_map<std::string, Data *> store;

public:
  /* Adds a data item to the database
   * @param key the lookup key
   * @param data pointer to stored data
   */
  void add(const std::string &key, Data *data);

  /* Gets a data item from the database
   * @param key the lookup key
   * @return Data* value the stored pointer, nullptr if not found
   */
  Data *get(const std::string &key) const;

  /* Removes a data item from the database
   * @param key the lookup key
   */
  void remove(const std::string &key);

  /* Cleans up all owned data pointers
   * @return void
   */
  ~Database();
};
