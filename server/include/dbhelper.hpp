#include <mysql/mysql.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <appinfo.hpp>
#include <block.hpp>
#include <serializer.hpp>

#ifndef DBHELPER
#define DBHELPER

class DBHelper {

private:
  static std::vector<Parameter> Separate(std::string sentence);
  static std::vector<std::vector<std::string>>
  RequestQuery(const std::string &command);

public:
  static std::vector<Block> RequestAllBlocks();
  static void LogData(const std::string &data);
};

#endif
