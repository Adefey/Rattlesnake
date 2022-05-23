#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <memory>
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
  NODATA = 0,
  SENDBLOCKS = 1,
  PROCESSSCHEME = 2,
};

class ServerApplication {

private:
  DBHelper db_helper;
  MachineFactory machine_factory;
  NetServer net_server;
  QUERY SelectQuery(const std::string &query);

public:
  ServerApplication();
  void ProcessEvents();
  //Точка входа подключений
  void ProcessUser(User &user, NetMessage &message);
  //Обработать запрос на обработку блок-схемы
  void ProcessStat(User &user);
  //Обработать запрос на сбор статистики
};

#endif
