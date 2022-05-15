#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include <parser.hpp>

#ifndef APPINFO
#define APPINFO

class AppInfo {

private:
  inline static const std::string config_path = "cfg.txt";
  static std::string GetProperty(const std::string &propertyName);

public:
  static std::string GetDBAddress();
  static std::string GetDBUsername();
  static std::string GetDBPassword();
  static std::string GetDBDatabase();
  static std::string GetDBBlockTable();
  static std::string GetDBLogTable();
  static size_t GetMaxMachinesCount();
  static size_t GetRefreshPeriod();
  static size_t GetPort();
};

#endif
