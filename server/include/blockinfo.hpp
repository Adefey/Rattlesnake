#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include <block.hpp>
#include <parser.hpp>

#ifndef BLOCKINFO
#define BLOCKINFO

class BlockInfo {

private:
  static std::string GetProperty(const std::string &propertyName,
                                 const std::string &path);

public:
  static std::string GetBlockSolverPath(const std::string &path);
  static std::string GetBlockGivenVars(const std::string &path);
  static std::string GetBlockSolvedVars(const std::string &path);
  static std::string GetBlockName(const std::string &path);
  static std::string GetBlockDescription(const std::string &path);
  static std::string GetBlockAuthorName(const std::string &path);
  static int GetBlockColor(const std::string &path);
};

#endif
