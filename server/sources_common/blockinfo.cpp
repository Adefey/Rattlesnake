#include <blockinfo.hpp>

std::string BlockInfo::GetProperty(const std::string &propertyName,
                                   const std::string &path) {
  std::ifstream reader;
  reader.open(path);
  if (reader.fail()) {
    throw std::runtime_error("Unable to open file");
  }
  std::string line = "";
  while (std::getline(reader, line)) {
    if (line == "#Python block config end") {
      throw std::runtime_error("Unable to find block property");
    }
    if (line.find(propertyName) != std::string::npos) {
      reader.close();
      size_t ind = line.find("=") + 1;
      std::string result = line.substr(ind);
      return result;
    }
  }
  reader.close();
  throw std::runtime_error("Unable to find block property");
}

std::string BlockInfo::GetBlockSolverPath(const std::string &path) {
  return GetProperty("SolverPath", path);
}

std::string BlockInfo::GetBlockGivenVars(const std::string &path) {
  return GetProperty("GivenVars", path);
}

std::string BlockInfo::GetBlockSolvedVars(const std::string &path) {
  return GetProperty("SolvedVars", path);
}

std::string BlockInfo::GetBlockName(const std::string &path) {
  return GetProperty("Name", path);
}

std::string BlockInfo::GetBlockDescription(const std::string &path) {
  return GetProperty("Description", path);
}

std::string BlockInfo::GetBlockAuthorName(const std::string &path) {
  return GetProperty("AuthorName", path);
}

int BlockInfo::GetBlockColor(const std::string &path) {
  return std::stoi(GetProperty("Color", path));
}
