#include <dbhelper.hpp>

DBHelper::DBHelper(){}

DBHelper:: DBHelper(std::string address, std::string username, std::string password,
           std::string database)
      : db_address(address), db_username(username), db_password(password),
        db_database(database) {}

Block DBHelper::RequestBlock(std::string name) {
    Block b;
    return b;
}
std::vector<Block> DBHelper::RequestAllBlocks() {
  std::vector<Block> v;
  return v;
}
void DBHelper::LogData(std::string data) {}
