#include <dbhelper.hpp>

std::string DBHelper::RequestQuery(const std::string &command) { return ""; }

DBHelper::DBHelper() {}

DBHelper::DBHelper(const std::string &address, const std::string &username,
                   const std::string &password, const std::string &database)
    : db_address(address), db_username(username), db_password(password),
      db_database(database) {}

Block DBHelper::RequestBlock(const std::string &name) {
  Block b;
  return b;
}
std::vector<Block> DBHelper::RequestAllBlocks() {
  std::vector<Block> v;
  return v;
}
void DBHelper::LogData(const std::string &data) {}
