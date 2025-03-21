#include <dbhelper.hpp>

std::vector<Parameter> DBHelper::Separate(std::string sentence) {
  sentence += ' ';
  std::vector<std::string> word_vector = {};
  std::stringstream ss(sentence);
  if (sentence != " " && sentence != "") {
    std::string tmp = "";
    while (getline(ss, tmp, ' ')) {
      word_vector.push_back(tmp);
    }
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
    mysql_close(connection);
    throw std::runtime_error("Unable to send a request");
  }
  res = mysql_store_result(connection);
  std::vector<std::vector<std::string>> result = {};
  if (res) {
    while ((row = mysql_fetch_row(res)) != NULL) {
      size_t col_count = mysql_num_fields(res);
      result.resize(result.size() + 1);
      for (size_t i = 0; i < col_count; ++i) {
        result.back().push_back(row[i]);
      }
    }
    mysql_free_result(res);
  }
  mysql_close(connection);
  delete[] query;
  return result;
}

std::vector<Block> DBHelper::RequestAllBlocks() {
  std::string query = "select * from " + AppInfo::GetDBBlockTable();
  std::vector<std::vector<std::string>> answer = RequestQuery(query);

  std::vector<Block> blocks = {};
  for (auto block_data : answer) {
    std::string solver_path = block_data[1];
    std::string given_vars = block_data[2];
    std::string solved_vars = block_data[3];
    std::string name = block_data[4];
    std::string description = block_data[5];
    std::string author_name = block_data[6];
    int color = std::stoi(block_data[7]);
    std::vector<Parameter> given = Separate(given_vars);
    std::vector<Parameter> solved = Separate(solved_vars);
    Block buf = Block(solver_path, given, solved, name, description,
                      author_name, color);
    blocks.push_back(buf);
  }

  return blocks;
}

void DBHelper::AddBlock(const std::string &SolverPath,
                        const std::string &GivenVars,
                        const std::string &SolvedVars, const std::string &Name,
                        const std::string &Description,
                        const std::string &AuthorName, const int Color) {
  std::string query = "insert " + AppInfo::GetDBBlockTable() +
                      " (solver_path, given_vars, solved_vars, name, "
                      "description, author_name, color) values ( \'" +
                      SolverPath + "\', \'" + GivenVars + "\', \'" +
                      SolvedVars + "\', \'" + Name + "\', \'" + Description +
                      "\', \'" + AuthorName + "\', " + std::to_string(Color) +
                      ")";
  RequestQuery(query);
}

void DBHelper::LogData(const std::string &data) {
  std::string query =
      "insert " + AppInfo::GetDBLogTable() + "(data) values (\'" + data + "\')";
  RequestQuery(query);
}

void DBHelper::PrepareTables() {
  try {
    std::cout << "Проверка, нужна ли миграция" << std::endl;
    std::string query = "select count(*) from " + AppInfo::GetDBBlockTable();
    RequestQuery(query);
    query = "select count(*) from " + AppInfo::GetDBLogTable();
    RequestQuery(query);
  } catch (const std::runtime_error &) {
    std::cout << "Начинается миграция" << std::endl;
    std::string create_blocks_table =
        "create table blocks( id int not null primary key AUTO_INCREMENT, "
        "solver_path text, given_vars text, solved_vars text, name text, "
        "description text, author_name text, color int);";
    RequestQuery(create_blocks_table);
    std::string create_logs_table =
        "create table logs( id int not null primary key AUTO_INCREMENT, date "
        "timestamp not null default CURRENT_TIMESTAMP, data text)";
    RequestQuery(create_logs_table);
    std::string path = "./blocks";
    for (const auto &file : std::filesystem::directory_iterator(path)) {
      std::string SolverPath = BlockInfo::GetBlockSolverPath(file.path());
      std::string GivenVars = BlockInfo::GetBlockGivenVars(file.path());
      std::string SolvedVars = BlockInfo::GetBlockSolvedVars(file.path());
      std::string Name = BlockInfo::GetBlockName(file.path());
      std::string Description = BlockInfo::GetBlockDescription(file.path());
      std::string AuthorName = BlockInfo::GetBlockAuthorName(file.path());
      int Color = BlockInfo::GetBlockColor(file.path());
      AddBlock(SolverPath, GivenVars, SolvedVars, Name, Description, AuthorName,
               Color);
    }
    std::cout << "Миграция завершена. Создана таблица с блоками и с логами"
              << std::endl;
  }
}
