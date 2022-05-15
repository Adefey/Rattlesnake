#include <dbhelper.hpp>

std::vector<Parameter> DBHelper::Separate(std::string sentence) {
  sentence += ' ';
  std::vector<std::string> word_vector;
  std::string result_word;
  for (size_t i = 0; i < sentence.size(); ++i) {
    char character = sentence[i];
    if (character == ' ' && result_word.size() != 0) {
      word_vector.push_back(result_word);
      result_word = "";
    } else {
      result_word += character;
    }
  }

  std::vector<Parameter> res = {};
  for (auto e : word_vector) {
    res.push_back(Parameter(e, "0"));
  }
  return res;
}

std::vector<Block> DBHelper::RequestQuery(const std::string &command) {
  //Использую Си стиль, так как mysql.h это сишная библиотека
  MYSQL *connection;
  MYSQL_RES *res;
  MYSQL_ROW row;
  connection = mysql_init(NULL);
  if (!connection) {
    throw std::runtime_error("Descriptor not obtained");
  }
  if (!mysql_real_connect(connection, db_address.c_str(), db_username.c_str(),
                          db_password.c_str(), db_database.c_str(), 0, NULL,
                          0)) {
    throw std::runtime_error("Unable to connect");
  }
  mysql_set_character_set(connection, "utf8");
  size_t l = command.length() + 1;
  char *query = new char[l];
  std::strncpy(query, command.c_str(), l);
  if (mysql_query(connection, query)) {
    delete[] query;
    throw std::runtime_error("Unable to send a request");
  }
  std::vector<Block> blocks = {};
  res = mysql_store_result(connection);
  while ((row = mysql_fetch_row(res)) != NULL) {
    std::string solver_path = row[1];
    std::string given_vars = row[2];
    std::string solved_vars = row[3];
    std::string name = row[4];
    std::string description = row[5];
    std::string author_name = row[6];
    int color = std::stoi(row[7]);
    std::vector<Parameter> given = Separate(given_vars);
    std::vector<Parameter> solved = Separate(solved_vars);
    Block buf = Block(solver_path, given, solved, name, description,
                      author_name, color);
    blocks.push_back(buf);
  }
  mysql_free_result(res);
  mysql_close(connection);
  delete[] query;
  return blocks;
}

DBHelper::DBHelper() {}

DBHelper::DBHelper(const std::string &address, const std::string &username,
                   const std::string &password, const std::string &database)
    : db_address(address), db_username(username), db_password(password),
      db_database(database) {}

Block DBHelper::RequestBlock(const std::string &name) { // DEPRECATED
  std::string query = "select * from " + AppInfo::GetDBBlockTable() +
                      " where name=\'" + name + "\'";
  std::vector<Block> blocks = RequestQuery(query);
  return blocks[0];
}
std::vector<Block> DBHelper::RequestAllBlocks() {
  std::string query = "select * from " + AppInfo::GetDBBlockTable();
  std::vector<Block> blocks = RequestQuery(query);
  return blocks;
}
void DBHelper::LogData(const std::string &data) {
  std::string query =
      "insert " + AppInfo::GetDBLogTable() + "(data) values (\'" + data + "\')";
  RequestQuery(query);
}
