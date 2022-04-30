#include <server_application.hpp>

ServerApplication::ServerApplication() {
  db_helper = DBHelper(AppInfo::GetDBAddress(), AppInfo::GetDBUsername(),
                       AppInfo::GetDBPassword(), AppInfo::GetDBDatabase());
}

void ServerApplication::ProcessEvents() {
  //Точка входа подключений
  std::cout << "Server launched\n" << '\n';
  std::cout << AppInfo::GetDBAddress() << '\n';
  std::cout << AppInfo::GetDBUsername() << '\n';
  std::cout << AppInfo::GetDBPassword() << '\n';
  std::cout << AppInfo::GetDBDatabase() << '\n';
  std::cout << AppInfo::GetDBBlockTable() << '\n';
  std::cout << AppInfo::GetDBLogTable() << '\n';
  std::cout << AppInfo::GetMaxMachinesCount() << '\n';
  std::cout << AppInfo::GetRefreshPeriod() << '\n';
  while (true) {
    //Тут будет получение сообщений в цикле
    std::string data = "";
    std::cout << "Working..." << '\n';
    // data = net_server.ReceiveData() тут будет, линтер душнит
    if (true) {
      switch (SelectQuery(data)) {
      case SENDBLOCKS: {
        ProcessStat();
        break;
      }
      case PROCESSSCHEME: {
        User user;
        ProcessUser(user);
      }
      }
    }
    usleep(AppInfo::GetRefreshPeriod() * 1000 * 100);
  }
}

QUERY ServerApplication::SelectQuery(const std::string &query) {
  //Выбор обработчика запроса
  return SENDBLOCKS;
}

void ServerApplication::ProcessUser(const User &user)
//Обработать запрос на обработку блок-схемы
{}

void ServerApplication::ProcessStat()
//Обработать запрос на сбор статистики
{}
