#include "data.h"
#include <vector>

void Database::add(const std::string &key, Table *table) {
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
  records[key] = record;
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

Table::~Table() {
  for (auto &pair : records) {
    delete pair.second;
  }
}