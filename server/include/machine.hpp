#include <block.hpp>
#include <dbhelper.hpp>
#include <user.hpp>
#include <vector>
#include <string>

#ifndef MACHINE
#define MACHINE

class Machine
{
private:
    User user;
    void ProcessOneBlock(std::string launch_string);
    std::string MakeProcessStartString(std::string block_name);
public:
    Machine();
    Machine(std::string start_params);
    std::string ProcessAllBlocks();
};

#endif
