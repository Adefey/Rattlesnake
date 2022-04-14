#include <block.hpp>
#include <vector>
#include <user.hpp>
#include <memory>

#ifndef MACHINEFACTORY
#define MACHINEFACTORY

class MachineFactory {
private:
    std::vector<std::string> machines_online;
    std::string MakeStartString(std::unique_ptr<User> user);
    void LaunchProcess(std::string launch_string);
public:
    MachineFactory();
    std::string ProcessMachine(std::unique_ptr<User> user); //запускает в докере
};

#endif
