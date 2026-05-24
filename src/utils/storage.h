#pragma once

#include <filesystem>
#include <string>

namespace Storage {
/* Returns the path to the data directory
 * @return std::filesystem::path& path reference
 */
const std::filesystem::path &dataDir();

/* Returns the filename for products storage
 * @return std::string& filename
 */
const std::string &productsFile();

/* Returns the filename for statistics storage
 * @return std::string& filename
 */
const std::string &statisticsFile();

/* Loads all storage files into memory
 * @return bool true on success, false on failure
 */
bool loadAll();

/* Saves all in-memory data to persistent storage
 * @return bool true on success, false on failure
 */
bool saveAll();

/* Saves temporary data to disk
 * @return bool true on success, false on failure
 */
bool saveTemp();
}