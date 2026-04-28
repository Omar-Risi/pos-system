#include "data.h"

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
