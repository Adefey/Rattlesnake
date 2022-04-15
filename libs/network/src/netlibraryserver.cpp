#include "netlibraryserver.hpp"

bool NetLibraryServer::SendData(NetSocket socket, std::string data) {}

bool NetLibraryServer::SendBlocksJson(NetServer server, std::string blocks) {}

bool NetLibraryServer::SendResultsJson(NetServer server, std::string results) {}

std::string NetLibraryServer::ReceiveData(NetSocket socket) {}

std::string NetLibraryServer::ReceiveBlocksJson(NetServer server) {}
