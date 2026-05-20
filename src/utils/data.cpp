#include "data.h"
#include <utility>
#include <vector>

void Database::add(const std::string &key, Table *table) {
  auto it = tables.find(key);
  if (it != tables.end()) {
    delete it->second;
  }
  tables[key] = table;
}

Table *Database::get(const std::string &key) const {
  auto it = tables.find(key);
  if (it == tables.end()) {
    return nullptr;
  }

  return it->second;
}

void Database::remove(const std::string &key) {
  auto it = tables.find(key);
  if (it != tables.end()) {
    delete it->second;
    tables.erase(it);
  }
}

Database::~Database() {
  for (auto &pair : tables) {
    delete pair.second;
  }
}

void Table::add(const std::string &key, Record *record) {
  auto it = records.find(key);
  if (it != records.end()) {
    delete it->second;
  }
  records[key] = record;
}

void Table::setColumns(const std::vector<std::string> &value) { columns = value; }

const std::vector<std::string> &Table::getColumns() const { return columns; }

void Table::setRowFactory(std::function<Record *(const std::unordered_map<std::string, std::string> &)> factory) {
  rowFactory = std::move(factory);
}

Record *Table::createRecordFromRow(const std::unordered_map<std::string, std::string> &row) const {
  if (!rowFactory) {
    return nullptr;
  }

  return rowFactory(row);
}

Record *Table::get(const std::string &key) const {
  auto it = records.find(key);
  if (it == records.end()) {
    return nullptr;
  }

  return it->second;
}

std::vector<Record *> Table::getAll(int max) const {
  std::vector<Record *> result;
  for (const auto &pair : records) {
    if (max != -1 && result.size() >= static_cast<size_t>(max)) {
      break;
    }
    result.push_back(pair.second);
  }
  return result;
}

void Table::remove(const std::string &key) {
  auto it = records.find(key);
  if (it != records.end()) {
    delete it->second;
    records.erase(it);
  }
}

void Table::clear() {
  for (auto &pair : records) {
    delete pair.second;
  }
  records.clear();
}

Table::~Table() {
  clear();
}