#include "netlibraryclient.hpp"

bool NetLibraryClient::SendBlocksRequest(NetClient& sender) {
  if (!sender.ConnectToServer()) {
    return false;
  }
  std::string header = "BlocksRequest";
  std::string content = " ";
  return SendData(sender.GetClientSocket(), NetMessage(header, content));
}

bool NetLibraryClient::SendParametersJson(NetClient& sender, const std::string& params) {
  std::string header = "ParametersRequest";
  return SendData(sender.GetClientSocket(), NetMessage(header, params));
}

bool NetLibraryClient::SendSchemeJson(NetClient& sender, const std::string& scheme, const std::string& parameters) {
  if (!sender.ConnectToServer()) {
    return false;
  }
  std::string header = "SchemeRequest";
  bool result = SendData(sender.GetClientSocket(), NetMessage(header, scheme));
  if (!result) {
    return false;
  }
  return SendParametersJson(sender, parameters);
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
