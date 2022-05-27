#include <mysql/mysql.h>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <appinfo.hpp>
#include <block.hpp>
#include <blockinfo.hpp>
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
  static void AddBlock(const std::string &SolverPath,
                       const std::string &GivenVars,
                       const std::string &SolvedVars, const std::string &Name,
                       const std::string &Description,
                       const std::string &AuthorName, const int Color);
  static void LogData(const std::string &data);
  static void PrepareTables();
};

#endif
