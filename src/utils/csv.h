#pragma once
#include "data.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

class Csv {
private:
  std::ifstream input_stream;
  std::ofstream output_stream;

  static std::vector<std::string> parseRow(const std::string &row);
  static std::string serializeCell(const std::string &value);
  static std::string joinRow(const std::vector<std::string> &row);
  static std::unordered_map<std::string, std::string>
  rowToMap(const std::vector<std::string> &columns,
           const std::vector<std::string> &values);

public:
  Csv() = default;
  ~Csv();

  static void writeFile(const std::filesystem::path &folder_path,
                        const std::string &file_name, const std::string &data);

  bool loadFile(Table &table, const std::filesystem::path &folder_path,
                const std::string &file_name);
  bool saveFile(const Table &table, const std::filesystem::path &folder_path,
                const std::string &file_name);
  bool saveTemp(const Table &table, const std::filesystem::path &folder_path,
                const std::string &file_name);
};
