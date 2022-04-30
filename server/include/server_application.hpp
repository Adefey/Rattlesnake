#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include <appinfo.hpp>
#include <block.hpp>
#include <dbhelper.hpp>
#include <machine_factory.hpp>
#include <netlibraryserver.hpp>
#include <netserver.hpp>
#include <parser.hpp>
#include <serializer.hpp>
#include <user.hpp>

#ifndef SERVERAPPLICATION
#define SERVERAPPLICATION

enum QUERY {
  SENDBLOCKS = 1,
  PROCESSSCHEME,
};

class ServerApplication {

private:
  DBHelper db_helper;
  //  std::queue<User> waiting_users; убрать
  //  std::queue<User> executing_users;
  //  std::queue<User> ready_users;
  MachineFactory machine_factory;
  NetLibraryServer net_server;
  QUERY SelectQuery(const std::string &query);

public:
  ServerApplication();
  void ProcessEvents();
  //Точка входа подключений
  void ProcessUser(const User &user);
  //Обработать запрос на обработку блок-схемы
  void ProcessStat();
  //Обработать запрос на сбор статистики
};

#endif
