#pragma once

#include <string>
#include <unordered_map>

// Base class for all storable types
class Record {
public:
  /* Displays this record item
   * @return void
   */
  virtual void
  display() const = 0; // pure virtual - every subclass must implement

  /* Virtual destructor for polymorphic cleanup
   * @return void
   */
  virtual ~Record() = default;
};

class Table {
  std::unordered_map<std::string, Record *> records;

public:
  /* Adds a record to the table
   * @param key the lookup key
   * @param record pointer to stored record
   */
  void add(const std::string &key, Record *data);

  /* Gets a record from the table
   * @param key the lookup key
   * @return Record* value the stored pointer, nultableslptr if not found
   */
  Record *get(const std::string &key) const;

  /* Removes a record from the table
   * @param key the lookup key
   */
  void remove(const std::string &key);

  /* Cleans up all owned data pointers
   * @return void
   */
  ~Table();
};

class Database {
  std::unordered_map<std::string, Table *> tables;

public:
  /* Adds a table to the database
   * @param key the lookup key
   * @param data pointer to stored data
   */
  void add(const std::string &key, Table *data);

  /* Gets a table from the database
   * @param key the lookup key
   * @return Table* value the stored pointer, nultableslptr if not found
   */
  Table *get(const std::string &key) const;

  /* Removes a data item from the database
   * @param key the lookup key
   */
  void remove(const std::string &key);

  /* Cleans up all owned data pointers
   * @return void
   */
  ~Database();
};
