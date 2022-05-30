#include <QMessageBox>
#include <cstring>
#include <fstream>
#include <iostream>
#include <parser.hpp>
#include <string>

#ifndef APPINFO
#define APPINFO

class AppInfo {
   private:
    inline static const std::string config_path = "cfg.txt";
    static std::string GetProperty(const std::string& propertyName);

   public:
    static size_t GetPort();
    static std::string GetIP();
};

#endif
