#include "netlibraryclient.hpp"

bool NetLibraryClient::SendData(NetSocket socket, std::string data) {}

bool NetLibraryClient::SendBlocksRequest(NetClient client) {}

bool NetLibraryClient::SendBlocksJson(NetClient client, std::string blocks) {}

bool NetLibraryClient::SendSchemeJson(NetClient client, std::string scheme) {}

std::string NetLibraryClient::ReceiveData(NetSocket socket) {}

std::string NetLibraryClient::ReceiveBlocksJson(NetClient client) {}
