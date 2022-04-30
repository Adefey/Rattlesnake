#include <appinfo.hpp>

const std::string AppInfo::config_path = "cfg.txt";

std::string AppInfo::GetProperty(const std::string &propertyName) {
  std::ifstream reader;
  reader.open(config_path);
  if (reader.fail()) {
    return "NOOPEN";
  }
  std::string line = "";
  while (std::getline(reader, line)) {
    if (line.find(propertyName) != std::string::npos) {
      reader.close();
      size_t ind = line.find("=") + 1;
      std::string result = line.substr(ind);
      return result;
    }
  }
  reader.close();
  return "NODATA";
}

std::string AppInfo::GetDBAddress() { return GetProperty("DBAddress"); }
std::string AppInfo::GetDBUsername() { return GetProperty("DBUsername"); }
std::string AppInfo::GetDBPassword() { return GetProperty("DBPassword"); }
std::string AppInfo::GetDBDatabase() { return GetProperty("DBDatabase"); }
std::string AppInfo::GetDBBlockTable() { return GetProperty("DBBlockTable"); }
std::string AppInfo::GetDBLogTable() { return GetProperty("DBLogTable"); }
size_t AppInfo::GetMaxMachinesCount() {
  return std::stoi(GetProperty("MaxMachinesCount"));
}
size_t AppInfo::GetRefreshPeriod() {
  return std::stoi(GetProperty("RefreshPeriod"));
}
