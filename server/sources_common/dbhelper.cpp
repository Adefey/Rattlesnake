#include <dbhelper.hpp>

std::string DBHelper::RequestQuery(const std::string &command) {
  //Использую Си стиль, так как mysql.h это сишная библиотека
  std::string result = "";
  MYSQL *connection;
  MYSQL_RES *res;
  MYSQL_ROW row;
  int l = 0;
  l = AppInfo::GetDBAddress().length() + 1;
  char *server = new char[l];
  std::strncpy(server, AppInfo::GetDBAddress().c_str(), l);
  l = AppInfo::GetDBUsername().length() + 1;
  char *user = new char[l];
  std::strncpy(user, AppInfo::GetDBUsername().c_str(), l);
  l = AppInfo::GetDBPassword().length() + 1;
  char *password = new char[AppInfo::GetDBPassword().length() + 1];
  std::strncpy(password, AppInfo::GetDBPassword().c_str(), l);
  l = AppInfo::GetDBDatabase().length() + 1;
  char *database = new char[l];
  std::strncpy(database, AppInfo::GetDBDatabase().c_str(), l);
  connection = mysql_init(NULL);
  if (!mysql_real_connect(connection, server, user, password, database, 0, NULL,
                          0)) {
    throw std::runtime_error("Unable to connect");
  }
  l = command.length() + 1;
  char *query = new char[l];
  std::strncpy(query, command.c_str(), l);
  if (mysql_query(connection, query)) {
    throw std::runtime_error("Unable to send a request");
  }
  res = mysql_use_result(connection);
  while ((row = mysql_fetch_row(res)) != NULL) {
    result += row[0];
  }
  mysql_free_result(res);
  mysql_close(connection);
  delete[] server;
  delete[] user;
  delete[] password;
  delete[] database;
  delete[] query;
  //Тут будет сериализация. Пока хз какой будет ответ
  return result;
}

DBHelper::DBHelper() {}

DBHelper::DBHelper(const std::string &address, const std::string &username,
                   const std::string &password, const std::string &database)
    : db_address(address), db_username(username), db_password(password),
      db_database(database) {}

Block DBHelper::RequestBlock(const std::string &name) {
  Block block;
  std::string query = "select * from " + AppInfo::GetDBBlockTable() +
                      " where name=\'" + name + "\'";
  std::string response = RequestQuery(query);
  Parser::ParseBlockFromJsonString(response, block);
  return block;
}
std::vector<Block> DBHelper::RequestAllBlocks() {
  std::vector<Block> blocks;
  std::string query = "select * from " + AppInfo::GetDBBlockTable();
  std::string response = RequestQuery(query);
  Parser::ParseBlocksFromJsonString(response, blocks);
  return blocks;
}
void DBHelper::LogData(const std::string &data) {
  std::string query =
      "insert into " + AppInfo::GetDBLogTable() + " values (\'" + data + "\')";
  RequestQuery(query);
}
