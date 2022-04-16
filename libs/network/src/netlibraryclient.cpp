#include "netlibraryclient.hpp"

bool NetLibraryClient::SendData(NetSocket socket, std::string data) {
  return false;
}

bool NetLibraryClient::SendBlocksRequest(NetClient client) {
  return false;
}

bool NetLibraryClient::SendBlocksJson(NetClient client, std::string blocks) {
  return false;
}

bool NetLibraryClient::SendSchemeJson(NetClient client, std::string scheme) {
  return false;
}

std::string NetLibraryClient::ReceiveData(NetSocket socket) {
  return "";
}

std::string NetLibraryClient::ReceiveBlocksJson(NetClient client) {
  return "";
}
