#include <mysql/mysql.h>
#include <vector>
#include <string>
#include <block.hpp>

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
  DBHelper(std::string address, std::string username, std::string password,
           std::string database)
      : db_address(address), db_username(username), db_password(password),
        db_database(database) {}
  Block RequestBlock(std::string name);
  std::vector<Block> RequestAllBlocks();
  void LogData(std::string data);
};

#endif
