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

  /* Writes raw data to a file located in folder_path/file_name
   * @param folder_path path to the destination folder
   * @param file_name name of the file to write
   * @param data the raw string data to write
   * @return void
   */
  static void writeFile(const std::filesystem::path &folder_path,
                        const std::string &file_name, const std::string &data);

  /* Loads CSV data from file into the provided table
   * @param table reference to destination Table
   * @param folder_path path to the folder containing the file
   * @param file_name file to read
   * @return bool true on success, false on failure
   */
  bool loadFile(Table &table, const std::filesystem::path &folder_path,
                const std::string &file_name);

  /* Saves table data to a CSV file
   * @param table source Table to serialize
   * @param folder_path destination folder path
   * @param file_name file to write
   * @return bool true on success, false on failure
   */
  bool saveFile(const Table &table, const std::filesystem::path &folder_path,
                const std::string &file_name);

  /* Saves table data to a temporary CSV file
   * @param table source Table to serialize
   * @param folder_path destination folder path
   * @param file_name temporary file name
   * @return bool true on success, false on failure
   */
  bool saveTemp(const Table &table, const std::filesystem::path &folder_path,
                const std::string &file_name);
};
