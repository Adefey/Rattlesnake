#include "netlibraryserver.hpp"

bool NetLibraryServer::SendBlocksJson(NetSocket& receiver, const std::string& blocks) {
  std::string header = "ListOfBlocks";
  NetMessage msg(header, blocks);
  bool is_sent = SendData(receiver, msg);
  receiver.CloseSocket();
  return is_sent;
}

bool NetLibraryServer::SendResultsJson(NetSocket& receiver, const std::string& results) {
  std::string header = "ResultsOfScheme";
  NetMessage msg(header, results);
  bool is_sent = SendData(receiver, msg);
  receiver.CloseSocket();
  return is_sent;
}

bool NetLibraryServer::ReceiveMessage(NetSocket& receiver, NetMessage& msg) {
  return ReceiveData(receiver, msg);
}
