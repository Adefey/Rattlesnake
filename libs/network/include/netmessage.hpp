#pragma once

#include <string>

class NetMessage {
 public:
  NetMessage() = default;
  NetMessage(const std::string& header, const std::string& content);

  NetMessage(const NetMessage&) = delete;
  NetMessage(NetMessage&&) = delete;

  NetMessage& operator=(const NetMessage&) = delete;
  NetMessage& operator=(NetMessage&&) noexcept;

  ~NetMessage() = default;

  std::string GetHeader() const;
  std::string GetContent() const;

 private:
  std::string header_;
  std::string content_;
};
