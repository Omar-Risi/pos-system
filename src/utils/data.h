#pragma once

#include <functional>
#include <string>
#include <vector>
#include <unordered_map>

// Base class for all storable types
class Record {
public:
  /* Displays this record item
   * @return void
   */
  virtual void
  display() const = 0;

  /* Converts the record into a CSV row
   * @return vector<string> the row values in column order
   */
  virtual std::vector<std::string> toCsvRow() const = 0;

  /* Virtual destructor for polymorphic cleanup
   * @return void
   */
  virtual ~Record() = default;
};

class Table {
  std::unordered_map<std::string, Record *> records;
  std::vector<std::string> columns;
  std::function<Record *(const std::unordered_map<std::string, std::string> &)> rowFactory;

public:
  /* Adds a record to the table
   * @param key the lookup key
   * @param record pointer to stored record
   */
  void add(const std::string &key, Record *data);

  /* Sets the table columns used for CSV import/export
   * @param value column names in CSV order
   */
  void setColumns(const std::vector<std::string> &value);

  /* Returns the table columns used for CSV import/export
   * @return vector<string> the CSV column names
   */
  const std::vector<std::string> &getColumns() const;

  /* Sets the factory used to build records from CSV rows
   * @param factory row factory callback
   */
  void setRowFactory(std::function<Record *(const std::unordered_map<std::string, std::string> &)> factory);

  /* Creates a record from a CSV row using the configured factory
   * @param row parsed CSV values keyed by column name
   * @return Record* the created record, or nullptr if no factory is set
   */
  Record *createRecordFromRow(const std::unordered_map<std::string, std::string> &row) const;

  /* Removes all records from the table
   */
  void clear();

  /* Gets a record from the table
   * @param key the lookup key
   * @return Record* value the stored pointer, nultableslptr if not found
   */
  Record *get(const std::string &key) const;

  /* Gets all records from the table
   * @param max the maximum number of records to return, -1 for all
   * @return vector<Record*> a vector of pointers to the stored records
   */
  std::vector<Record *> getAll(int max = -1) const;

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
