#pragma once

#include <filesystem>
#include <string>

namespace Storage {
const std::filesystem::path &dataDir();
const std::string &productsFile();
const std::string &statisticsFile();

bool loadAll();
bool saveAll();
bool saveTemp();
}