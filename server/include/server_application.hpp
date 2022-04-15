#include <memory>
#include <queue>
#include <string>
#include <vector>

#include <boost/asio.hpp>

#include <appinfo.hpp>
#include <block.hpp>
#include <dbhelper.hpp>
#include <machine_factory.hpp>
#include <netserver.hpp>
#include <parser.hpp>
#include <serializer.hpp>
#include <user.hpp>

#ifndef SERVERAPPLICATION
#define SERVERAPPLICATION

class ServerApplication {

private:
  DBHelper db_helper;
  std::queue<User> waiting_users;
  std::queue<User> executing_users;
  std::queue<User> ready_users;
  MachineFactory machine_factory;
  NetServer net_server;

public:
  ServerApplication();
  void ProcessEvents();
  //Точка входа подключений
  void ProcessUser(std::unique_ptr<User> user);
  //Обработать запрос на обработку блок-схемы
  void ProcessStat();
  //Обработать запрос на сбор статистики
};

#endif
