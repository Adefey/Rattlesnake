#include <mysql/mysql.h>

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
  std::string db_address;
  std::string db_username;
  std::string db_password;
  std::string db_database;
  std::string RequestQuery(const std::string &command);

public:
  DBHelper();
  DBHelper(const std::string &address, const std::string &username,
           const std::string &password, const std::string &database);
  Block RequestBlock(const std::string &name);
  std::vector<Block> RequestAllBlocks();
  void LogData(const std::string &data);
};

#endif
