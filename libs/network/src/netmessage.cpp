#include "netmessage.hpp"

NetMessage& NetMessage::operator=(NetMessage&& rhs) noexcept {
  this->content_ = std::move(rhs.content_);
  this->header_ = std::move(rhs.header_);
  return *this;
}

NetMessage::NetMessage(const std::string& header, const std::string& content)
    : header_(header), content_(content) {}

std::string NetMessage::GetHeader() const {
  return header_;
}

std::string NetMessage::GetContent() const {
  return content_;
}
