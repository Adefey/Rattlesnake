#include <block.hpp>
#include <vector>
#include <user.hpp>
#include <memory>

#ifndef MACHINEFACTORY
#define MACHINEFACTORY

class MachineFactory {
private:
    std::vector<std::string> machines_online;
public:
    std::string ProcessMachine(std::unique_ptr<User> user); //запускает в докере
};

#endif
