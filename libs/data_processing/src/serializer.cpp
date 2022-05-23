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
  json_value = nlohmann::json{{"solver_path", block.solver_path},
                              {"given_vars", block.given_vars},
                              {"solved_vars", block.solved_vars},
                              {"name", block.name},
                              {"description", block.description},
                              {"author_name", block.author_name},
                              {"color", block.color}};
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
