#include <parser.hpp>
#include <string>

#ifndef APPINFO
#define APPINFO

class AppInfo
{
private:
    std::string config_path = "cfg.txt"
public:
    static std::String GetDBAddress();
    static std::String GetDBUsername();
    static std::String GetDBPassword();
    static std::String GetDBDatabase();
    static std::String GetDBBlockTable();
    static std::String GetDBLogTable();
    static size_t MaxMachinesCount();
}

#endif
