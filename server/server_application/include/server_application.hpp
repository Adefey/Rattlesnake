#include <block.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <dbhelper.hpp>
#include <netserver.hpp>
#include <parser.hpp>
#include <queue>
#include <serializer.hpp>
#include <user.hpp>
#include <vector>
#include <string>
#include <machine_factory.hpp>
#include <memory>

#ifndef SERVERAPPLICATION
#define SERVERAPPLICATION

class ServerApplication {
private:
  boost::asio::deadline_timer timer;
  DBHelper db_helper;
  std::queue<User> waiting_users;
  std::queue<User> executing_users;
  std::queue<User> ready_users;
  MachineFactory machine_factory;
  NetServer net_server;

public:
  ServerApplication();
  void ProcessEvents(); //Точка входа подключений
  void ProcessUser(
      std::unique_ptr<User> user); //Обработать запрос на обработку блок-схемы
  void ProcessStat(); //Обработать запрос на сбор статистики
};

#endif
