#include "serializer.hpp"

#include "json.hpp"

std::string Serializer::ToString(const int value) {
  return std::to_string(value);
}

std::string Serializer::ToString(const double value) {
  return std::to_string(value);
}

void to_json(nlohmann::json& json_value, const Parameter& parameter) {
  json_value =
      nlohmann::json{{"param_name", parameter.param_name}, {"param_value", parameter.param_value}};
}

void to_json(nlohmann::json& json_value, const Block& block) {
  json_value = nlohmann::json{{"solver_path", block.GetSolverPath()},
                              {"given_vars", block.GetGivenVars()},
                              {"solved_vars", block.GetSolvedVars()},
                              {"name", block.GetName()},
                              {"description", block.GetDescription()},
                              {"author_name", block.GetAuthorName()},
                              {"color", block.GetColor()}};
}

std::string Serializer::ToJsonString(const Block& value) {
  nlohmann::json result = value;
  return to_string(result);
}

std::string Serializer::ToJsonString(const Parameter& value) {
  nlohmann::json result = value;
  return to_string(result);
}

std::string Serializer::ToJsonString(const std::vector<Block>& values) {
  nlohmann::json result = values;
  return to_string(result);
}

std::string Serializer::ToJsonString(const std::vector<Parameter>& values) {
  nlohmann::json result = values;
  return to_string(result);
}
