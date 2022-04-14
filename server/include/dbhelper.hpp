#include <mysql/mysql.h>
#include <vector>
#include <string>
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
  std::string RequestQuery(std::string);

public:
  DBHelper();
  DBHelper(std::string address, std::string username, std::string password, std::string database);
  Block RequestBlock(std::string name);
  std::vector<Block> RequestAllBlocks();
  void LogData(std::string data);
};

#endif
