#pragma once
#include <filesystem>
#include <iostream>
#include <vector>

/*
 * TODO: Add convert string vector to file columns
 * TODO: Add Read/Parse file
 * TODO: Add Check has columns method
 */

class Csv {
private:
public:
  static void writeFile(const std::filesystem::path &folder_path,
                        const std::string &file_name, const std::string &data);
};
