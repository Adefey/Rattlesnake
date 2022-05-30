#include <appinfo.h>

std::string AppInfo::GetProperty(const std::string& propertyName) {
    std::ifstream reader;
    reader.open(config_path);
    if (reader.fail()) {
        return "ERROR";
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

std::string AppInfo::GetIP() {
    return GetProperty("IP");
}
size_t AppInfo::GetPort() {
    return std::stoi(GetProperty("Port"));
}
