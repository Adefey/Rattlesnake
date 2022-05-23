#include <dbhelper.hpp>

std::vector<Parameter> DBHelper::Separate(std::string sentence) {
  sentence += ' ';
  std::vector<std::string> word_vector;
  std::stringstream ss(sentence);
  std::string tmp = "";
  while (getline(ss, tmp, ' ')) {
    word_vector.push_back(tmp);
  }
  std::vector<Parameter> res = {};
  for (auto e : word_vector) {
    res.push_back(Parameter(e, ""));
  }
  return res;
}

std::vector<std::vector<std::string>>
DBHelper::RequestQuery(const std::string &command) {
  std::string db_address = AppInfo::GetDBAddress();
  std::string db_username = AppInfo::GetDBUsername();
  std::string db_password = AppInfo::GetDBPassword();
  std::string db_database = AppInfo::GetDBDatabase();
  MYSQL *connection;
  MYSQL_RES *res;
  MYSQL_ROW row;
  connection = mysql_init(NULL);
  if (!connection) {
    throw std::runtime_error("Descriptor has not been obtained");
  }
  if (!mysql_real_connect(connection, db_address.c_str(), db_username.c_str(),
                          db_password.c_str(), db_database.c_str(), 0, NULL,
                          0)) {
    throw std::runtime_error("Unable to connect to DB");
  }
  mysql_set_character_set(connection, "utf8");
  size_t l = command.length() + 1;
  char *query = new char[l];
  std::strncpy(query, command.c_str(), l);
  if (mysql_query(connection, query)) {
    delete[] query;
    throw std::runtime_error("Unable to send a request");
  }
  res = mysql_store_result(connection);

  std::vector<std::vector<std::string>> result;
  while ((row = mysql_fetch_row(res)) != NULL) {
    result.resize(result.size() + 1);
    result.back().push_back(row[1]);
    result.back().push_back(row[2]);
    result.back().push_back(row[3]);
    result.back().push_back(row[4]);
    result.back().push_back(row[5]);
    result.back().push_back(row[6]);
    result.back().push_back(row[7]);
  }
  mysql_free_result(res);
  mysql_close(connection);
  delete[] query;
  return result;
}

std::vector<Block> DBHelper::RequestAllBlocks() {
  std::string query = "select * from " + AppInfo::GetDBBlockTable();
  std::vector<std::vector<std::string>> answer = RequestQuery(query);

  std::vector<Block> blocks = {};
  for (auto block_data : answer) {
    std::string solver_path = block_data[0];
    std::string given_vars = block_data[1];
    std::string solved_vars = block_data[2];
    std::string name = block_data[3];
    std::string description = block_data[4];
    std::string author_name = block_data[5];
    int color = std::stoi(block_data[6]);
    std::vector<Parameter> given = Separate(given_vars);
    std::vector<Parameter> solved = Separate(solved_vars);
    Block buf = Block(solver_path, given, solved, name, description,
                      author_name, color);
    blocks.push_back(buf);
  }

  return blocks;
}
void DBHelper::LogData(const std::string &data) {
  std::string query =
      "insert " + AppInfo::GetDBLogTable() + "(data) values (\'" + data + "\')";
  RequestQuery(query);
}
