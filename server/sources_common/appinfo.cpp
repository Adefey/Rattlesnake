#include <appinfo.hpp>

std::string AppInfo::GetProperty(const std::string &propertyName) {
  std::ifstream reader;
  reader.open(config_path);
  if (reader.fail()) {
    throw std::runtime_error("Unable to open file");
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
  throw std::runtime_error("Unable to find property");
}

std::string AppInfo::GetDBAddress() { return GetProperty("DBAddress"); }
std::string AppInfo::GetDBUsername() { return GetProperty("DBUsername"); }
std::string AppInfo::GetDBPassword() { return GetProperty("DBPassword"); }
std::string AppInfo::GetDBDatabase() { return GetProperty("DBDatabase"); }
std::string AppInfo::GetDBBlockTable() { return GetProperty("DBBlockTable"); }
std::string AppInfo::GetDBLogTable() { return GetProperty("DBLogTable"); }
std::string AppInfo::GetMachineName() { return GetProperty("MachineName"); }
size_t AppInfo::GetMaxMachinesCount() {
  return std::stoi(GetProperty("MaxMachinesCount"));
}
size_t AppInfo::GetRefreshPeriod() {
  return std::stoi(GetProperty("RefreshPeriod"));
}
size_t AppInfo::GetPort() { return std::stoi(GetProperty("Port")); }
