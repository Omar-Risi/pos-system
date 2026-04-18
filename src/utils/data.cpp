#include "data.h"

void Database::add(const std::string &key, Data *data) { store[key] = data; }

Data *Database::get(const std::string &key) const {
  auto it = store.find(key);
  if (it == store.end()) {
    return nullptr;
  }

  return it->second;
}

void Database::remove(const std::string &key) {
  auto it = store.find(key);
  if (it != store.end()) {
    delete it->second;
    store.erase(it);
  }
}

Database::~Database() {
  for (auto &pair : store) {
    delete pair.second;
  }
}
