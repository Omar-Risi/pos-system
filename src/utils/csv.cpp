#include "./csv.h"
#include "./io.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

namespace fs = std::filesystem;

Csv::~Csv() {
  if (input_stream.is_open()) {
    input_stream.close();
  }

  if (output_stream.is_open()) {
    output_stream.close();
  }
}

std::vector<std::string> Csv::parseRow(const std::string &row) {
  std::vector<std::string> values;
  std::string current;
  bool in_quotes = false;

  for (size_t i = 0; i < row.size(); ++i) {
    char ch = row[i];
    if (ch == '"') {
      if (in_quotes && i + 1 < row.size() && row[i + 1] == '"') {
        current.push_back('"');
        ++i;
      } else {
        in_quotes = !in_quotes;
      }
    } else if (ch == ',' && !in_quotes) {
      values.push_back(current);
      current.clear();
    } else {
      current.push_back(ch);
    }
  }

  values.push_back(current);
  return values;
}

std::string Csv::serializeCell(const std::string &value) {
  const bool needs_quotes = value.find_first_of(",\"\n\r") != std::string::npos;
  if (!needs_quotes) {
    return value;
  }

  std::string escaped = "\"";
  for (char ch : value) {
    if (ch == '"') {
      escaped += "\"\"";
    } else {
      escaped.push_back(ch);
    }
  }
  escaped.push_back('"');
  return escaped;
}

std::string Csv::joinRow(const std::vector<std::string> &row) {
  std::string result;
  for (size_t i = 0; i < row.size(); ++i) {
    if (i != 0) {
      result.push_back(',');
    }
    result += serializeCell(row[i]);
  }
  return result;
}

std::unordered_map<std::string, std::string>
Csv::rowToMap(const std::vector<std::string> &columns, const std::vector<std::string> &values) {
  std::unordered_map<std::string, std::string> row;
  size_t limit = columns.size();
  if (values.size() < limit) {
    limit = values.size();
  }

  for (size_t i = 0; i < limit; ++i) {
    row[columns[i]] = values[i];
  }

  return row;
}

void Csv::writeFile(const std::filesystem::path &folder_path,
                    const std::string &file_name, const std::string &data) {
  fs::path dir_path = fs::current_path() / folder_path;
  fs::path full_path = dir_path / file_name;

  std::error_code ec;
  fs::create_directories(dir_path, ec);

  if (ec) {
    IO::print("Error: " + ec.message());
    return;
  }

  // 3. Open the stream using the path object
  std::ofstream fstream(full_path);

  if (fstream.is_open()) {
    fstream << data << std::endl;
  }
}

bool Csv::loadFile(Table &table, const std::filesystem::path &folder_path, const std::string &file_name) {
  fs::path dir_path = fs::current_path() / folder_path;
  fs::path full_path = dir_path / file_name;

  input_stream.open(full_path);
  if (!input_stream.is_open()) {
    IO::print("Error: unable to open file for reading");
    return false;
  }

  std::string header_line;
  if (!std::getline(input_stream, header_line)) {
    input_stream.close();
    return false;
  }

  std::vector<std::string> file_columns = parseRow(header_line);
  if (table.getColumns().empty()) {
    table.setColumns(file_columns);
  }

  const std::vector<std::string> &table_columns = table.getColumns();
  table.clear();

  std::string row_line;
  while (std::getline(input_stream, row_line)) {
    if (row_line.empty()) {
      continue;
    }

    std::vector<std::string> values = parseRow(row_line);
    std::unordered_map<std::string, std::string> row = rowToMap(table_columns, values);
    if (table_columns.empty()) {
      continue;
    }

    Record *record = table.createRecordFromRow(row);
    if (record == nullptr) {
      continue;
    }

    table.add(row.at(table_columns.front()), record);
  }

  input_stream.close();
  return true;
}

bool Csv::saveFile(const Table &table, const std::filesystem::path &folder_path, const std::string &file_name) {
  fs::path dir_path = fs::current_path() / folder_path;
  fs::path full_path = dir_path / file_name;

  std::error_code ec;
  fs::create_directories(dir_path, ec);
  if (ec) {
    IO::print("Error: " + ec.message());
    return false;
  }

  output_stream.open(full_path, std::ios::trunc);
  if (!output_stream.is_open()) {
    IO::print("Error: unable to open file for writing");
    return false;
  }

  const std::vector<std::string> &columns = table.getColumns();
  if (!columns.empty()) {
    output_stream << joinRow(columns) << std::endl;
  }

  for (Record *record : table.getAll()) {
    if (record == nullptr) {
      continue;
    }
    output_stream << joinRow(record->toCsvRow()) << std::endl;
  }

  output_stream.close();
  return true;
}

bool Csv::saveTemp(const Table &table, const std::filesystem::path &folder_path, const std::string &file_name) {
  fs::path file_path = file_name;
  std::string temp_name = file_path.stem().string() + "-temp" + file_path.extension().string();
  return saveFile(table, folder_path, temp_name);
}
