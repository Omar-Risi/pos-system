#include "./csv.h"
#include "./io.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

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
