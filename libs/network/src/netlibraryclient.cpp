#include "netlibraryclient.hpp"

bool NetLibraryClient::SendBlocksRequest(NetClient& sender) {
  if (!sender.ConnectToServer()) {
    return false;
  }
  std::string header = "BlocksRequest";
  std::string content = " ";
  return SendData(sender.GetClientSocket(), NetMessage(header, content));
}

bool NetLibraryClient::SendSchemeJson(NetClient& sender, const std::string& scheme) {
  if (!sender.ConnectToServer()) {
    return false;
  }
  std::string header = "SchemeRequest";
  return SendData(sender.GetClientSocket(), NetMessage(header, scheme));
}

bool NetLibraryClient::ReceiveBlocksJson(NetClient& receiver, std::string& blocks) {
  NetMessage result;
  bool is_receive = ReceiveData(receiver.GetClientSocket(), result);
  receiver.DisconnectFromServer();
  if (is_receive) {
    blocks = result.GetContent();
    return true;
  }
  return false;
}

bool NetLibraryClient::ReceiveResultsJson(NetClient& receiver, std::string& results) {
  return ReceiveBlocksJson(receiver, results);
}
