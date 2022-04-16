#include "netlibraryserver.hpp"

NetLibraryServer::NetLibraryServer() = default;

NetLibraryServer::~NetLibraryServer() noexcept = default;

bool NetLibraryServer::SendData(NetSocket socket, std::string data) {
  return false;
}

bool NetLibraryServer::SendBlocksJson(NetServer server, std::string blocks) {
  return false;
}

bool NetLibraryServer::SendResultsJson(NetServer server, std::string results) {
  return false;
}

std::string NetLibraryServer::ReceiveData(NetSocket socket) {
  return "";
}

std::string NetLibraryServer::ReceiveBlocksJson(NetServer server) {
  return "";
}
