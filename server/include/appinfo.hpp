#include <cstring>
#include <string>

#include <parser.hpp>

#ifndef APPINFO
#define APPINFO

class AppInfo {

private:
  std::string config_path = "cfg.txt";

public:
  static std::string GetDBAddress();
  static std::string GetDBUsername();
  static std::string GetDBPassword();
  static std::string GetDBDatabase();
  static std::string GetDBBlockTable();
  static std::string GetDBLogTable();
  static size_t GetMaxMachinesCount();
  static size_t GetRefreshPeriod();
};

#endif
