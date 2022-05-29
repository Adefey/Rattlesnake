#include "parser.hpp"

#include "json.hpp"

bool Parser::ToInt(const std::string& value, int& result) {
  result = 0;
  try {
    result = std::stoi(value);
  } catch (std::invalid_argument const& ex) {
    return false;
  } catch (std::out_of_range const& ex) {
    return false;
  }
  return true;
}

bool Parser::ToDouble(const std::string& value, double& result) {
  result = 0;
  try {
    result = std::stod(value);
  } catch (std::invalid_argument const& ex) {
    return false;
  } catch (std::out_of_range const& ex) {
    return false;
  }
  return true;
}

void from_json(const nlohmann::json& json_value, Parameter& parameter) {
  if (json_value.find("param_name") != json_value.end()) {
    json_value.at("param_name").get_to(parameter.param_name);
  }
  if (json_value.find("param_value") != json_value.end()) {
    json_value.at("param_value").get_to(parameter.param_value);
  }
}

void from_json(const nlohmann::json& json_value, Block& block) {
  block.solved_vars.clear();
  block.given_vars.clear();

  if (json_value.find("solver_path") != json_value.end()) {
    json_value.at("solver_path").get_to(block.solver_path);
  }
  if (json_value.find("given_vars") != json_value.end()) {
    json_value.at("given_vars").get_to(block.given_vars);
  }
  if (json_value.find("solved_vars") != json_value.end()) {
    json_value.at("solved_vars").get_to(block.solved_vars);
  }
  if (json_value.find("name") != json_value.end()) {
    json_value.at("name").get_to(block.name);
  }
  if (json_value.find("description") != json_value.end()) {
    json_value.at("description").get_to(block.description);
  }
  if (json_value.find("author_name") != json_value.end()) {
    json_value.at("author_name").get_to(block.author_name);
  }
  if (json_value.find("color") != json_value.end()) {
    json_value.at("color").get_to(block.color);
  }
}

bool Parser::ParseParameterFromJsonString(const std::string& val, Parameter& result) {
  nlohmann::json json_value = nlohmann::json::parse(val, nullptr, false);

  if (json_value.is_discarded()) {
    return false;
  }
  if (json_value.find("param_name") == json_value.end() ||
      json_value.find("param_value") == json_value.end()) {
    return false;
  }

  json_value.get_to(result);
  return true;
}

bool Parser::ParseParametersFromJsonString(const std::string& val, std::vector<Parameter>& result) {
  nlohmann::json json_value = nlohmann::json::parse(val, nullptr, false);

  if (json_value.is_discarded()) {
    return false;
  }

  if (!result.empty()) {
    result.clear();
  }

  for (auto& el : json_value) {
    Parameter tmp;
    if (ParseParameterFromJsonString(to_string(el), tmp)) {
      result.push_back(tmp);
    }
  }

  return !result.empty();
}

bool Parser::ParseBlockFromJsonString(const std::string& val, Block& result) {
  nlohmann::json json_value = nlohmann::json::parse(val, nullptr, false);

  if (json_value.is_discarded()) {
    return false;
  }
  if (json_value.find("solver_path") == json_value.end() ||
      json_value.find("given_vars") == json_value.end() ||
      json_value.find("solved_vars") == json_value.end() ||
      json_value.find("name") == json_value.end() ||
      json_value.find("description") == json_value.end() ||
      json_value.find("author_name") == json_value.end() ||
      json_value.find("color") == json_value.end()) {
    return false;
  }

  json_value.get_to(result);
  return true;
}

bool Parser::ParseBlocksFromJsonString(const std::string& val, std::vector<Block>& result) {
  nlohmann::json json_value = nlohmann::json::parse(val, nullptr, false);

  if (json_value.is_discarded()) {
    return false;
  }

  if (!result.empty()) {
    result.clear();
  }

  for (auto& el : json_value) {
    Block tmp;
    if (ParseBlockFromJsonString(to_string(el), tmp)) {
      result.push_back(tmp);
    }
  }

  return !result.empty();
}
