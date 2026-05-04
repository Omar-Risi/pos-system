#pragma once
#include <filesystem>
#include <iostream>
#include <vector>

class Csv {
private:
public:
  static void writeFile(const std::filesystem::path &folder_path,
                        const std::string &file_name, const std::string &data);
};
