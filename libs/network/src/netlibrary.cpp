#include "netlibrary.hpp"

#include <sys/socket.h>

#include <stdexcept>

bool NetLibrary::ReceiveString(NetSocket& socket, std::string& str, size_t str_size) {
  bool is_correct_recv = true;
  char* buffer = new char[str_size + 1];
  buffer[str_size] = '\0';

  int fd = socket.GetSocket();

  ssize_t bytes_read = 0;
  ssize_t read_bytes_count = 0;
  while (bytes_read < str_size) {
    read_bytes_count = recv(fd, buffer + bytes_read, str_size - bytes_read, 0);
    if (read_bytes_count == -1) {
      is_correct_recv = false;
      break;
    }
    if (read_bytes_count == 0) {
      is_correct_recv = false;
      break;
    }
    bytes_read += read_bytes_count;
  }

  if (is_correct_recv) {
    str = std::string(buffer);
  }
  delete[] buffer;

  return is_correct_recv;
}

bool NetLibrary::ReceiveData(NetSocket& socket, NetMessage& msg) {
  if (!socket.IsSocketOpen()) {
    return false;
  }

  std::string header_length_str;
  if (!ReceiveString(socket, header_length_str, base_string_length)) {
    return false;
  }

  std::string header;
  try {
    size_t header_length = std::stoul(header_length_str);
    if (!ReceiveString(socket, header, header_length)) {
      return false;
    }
  } catch (std::invalid_argument const& ex) {
    throw std::invalid_argument("Incorrect header length received from client: " + header_length_str);
  }

  std::string content_length_str;
  if (!ReceiveString(socket, content_length_str, base_string_length)) {
    return false;
  }

  std::string content;
  try {
    size_t content_length = std::stoul(content_length_str);
    if (!ReceiveString(socket, content, content_length)) {
      return false;
    }
  } catch (std::invalid_argument const& ex) {
    throw std::invalid_argument("Incorrect content length received from client: " + content_length_str);
  }

  msg = NetMessage(header, content);
  return true;
}

bool NetLibrary::SendString(NetSocket& socket, const std::string& str) {
  bool is_correct_sent = true;
  size_t symbols_left = str.size();
  ssize_t sent = 0;

  int fd = socket.GetSocket();
  while (symbols_left > 0) {
    sent = send(fd, str.data() + sent, str.size() - sent, 0);
    if (sent == -1) {
      is_correct_sent = false;
      break;
    }
    symbols_left -= sent;
  }

  return is_correct_sent;
}

bool NetLibrary::SendData(NetSocket& socket, const NetMessage& message) {
  if (!socket.IsSocketOpen()) {
    return false;
  }

  std::string header_length = std::to_string(message.GetHeader().length());
  while (header_length.length() < base_string_length) {
    header_length = " " + header_length;
  }
  if (!SendString(socket, header_length)) {
    return false;
  }
  if (!SendString(socket, message.GetHeader())) {
    return false;
  }

  std::string content_length = std::to_string(message.GetContent().length());
  while (content_length.length() < base_string_length) {
    content_length = " " + content_length;
  }
  if (!SendString(socket, content_length)) {
    return false;
  }
  if (!SendString(socket, message.GetContent())) {
    return false;
  }

  return true;
}
