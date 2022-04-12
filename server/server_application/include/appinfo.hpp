#include <parser.hpp>
#include <string>

#ifndef APPINFO
#define APPINFO

class AppInfo
{
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
}

#endif
