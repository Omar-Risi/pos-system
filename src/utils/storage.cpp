#include "storage.h"
#include "csv.h"
#include "data.h"
#include "service.h"
#include "../models/statistics.h"
#include <filesystem>
#include <string>

namespace Storage {
namespace fs = std::filesystem;

const fs::path &dataDir() {
  static const fs::path path("assets/data");
  return path;
}

const std::string &productsFile() {
  static const std::string name("products.csv");
  return name;
}

const std::string &statisticsFile() {
  static const std::string name("statistics.csv");
  return name;
}

static bool loadIfExists(Csv &csv, Table *table, const fs::path &folder,
                         const std::string &file_name) {
  if (!table) {
    return false;
  }
  fs::path full_path = fs::current_path() / folder / file_name;
  if (!fs::exists(full_path)) {
    return false;
  }
  return csv.loadFile(*table, folder, file_name);
}

static std::string tempFileName(const std::string &file_name) {
  fs::path file_path = file_name;
  return file_path.stem().string() + "-temp" + file_path.extension().string();
}

static bool loadPreferTemp(Csv &csv, Table *table, const fs::path &folder,
                           const std::string &file_name) {
  if (!table) {
    return false;
  }

  const std::string temp_name = tempFileName(file_name);
  fs::path temp_path = fs::current_path() / folder / temp_name;
  if (fs::exists(temp_path)) {
    return csv.loadFile(*table, folder, temp_name);
  }

  return loadIfExists(csv, table, folder, file_name);
}

static void syncTotalProducts(Table *products, Table *stats) {
  if (!stats) {
    return;
  }
  Statistics *total =
      dynamic_cast<Statistics *>(stats->get("total_products"));
  if (!total) {
    return;
  }
  int count = 0;
  if (products) {
    count = static_cast<int>(products->getAll().size());
  }
  total->setValue(count);
}

bool loadAll() {
  Database *db = Service::getDatabase();
  if (!db) {
    return false;
  }

  Table *products = db->get("products");
  Table *stats = db->get("statistics");
  Csv csv;

    bool loaded_products =
      loadPreferTemp(csv, products, dataDir(), productsFile());
    bool loaded_stats =
      loadPreferTemp(csv, stats, dataDir(), statisticsFile());

  syncTotalProducts(products, stats);
  return loaded_products || loaded_stats;
}

bool saveAll() {
  Database *db = Service::getDatabase();
  if (!db) {
    return false;
  }

  Csv csv;
  bool ok = true;

  Table *products = db->get("products");
  if (products) {
    ok = csv.saveFile(*products, dataDir(), productsFile()) && ok;
  }

  Table *stats = db->get("statistics");
  if (stats) {
    ok = csv.saveFile(*stats, dataDir(), statisticsFile()) && ok;
  }

  if (ok) {
    std::error_code ec;
    fs::remove(fs::current_path() / dataDir() / tempFileName(productsFile()),
               ec);
    fs::remove(fs::current_path() / dataDir() / tempFileName(statisticsFile()),
               ec);
  }

  return ok;
}

bool saveTemp() {
  Database *db = Service::getDatabase();
  if (!db) {
    return false;
  }

  Csv csv;
  bool ok = true;

  Table *products = db->get("products");
  if (products) {
    ok = csv.saveTemp(*products, dataDir(), productsFile()) && ok;
  }

  Table *stats = db->get("statistics");
  if (stats) {
    ok = csv.saveTemp(*stats, dataDir(), statisticsFile()) && ok;
  }

  return ok;
}
}