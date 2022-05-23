#include <server_application.hpp>

ServerApplication::ServerApplication() {
  int port = AppInfo::GetPort();
  net_server.InitializeServer(port);
}

void ServerApplication::ProcessEvents() {
  //Точка входа подключений
  std::cout << "Сервер запущен со следующими параметрами" << std::endl;
  std::cout << "Адрес СУБД: " << AppInfo::GetDBAddress() << std::endl;
  std::cout << "Юзер СУБД: " << AppInfo::GetDBUsername() << std::endl;
  std::cout << "Пароль СУБД: " << AppInfo::GetDBPassword() << std::endl;
  std::cout << "База данных СУБД: " << AppInfo::GetDBDatabase() << std::endl;
  std::cout << "Таблица блоков СУБД: " << AppInfo::GetDBBlockTable()
            << std::endl;
  std::cout << "Таблица логов СУБД: " << AppInfo::GetDBLogTable() << std::endl;
  std::cout << "Максимальное число онлайн машин: "
            << AppInfo::GetMaxMachinesCount() << std::endl;
  std::cout << "Интервал обновления: " << AppInfo::GetRefreshPeriod()
            << std::endl;
  std::cout << "Порт: " << AppInfo::GetPort() << std::endl;
  std::cout << "Имя машины: " << AppInfo::GetMachineName() << std::endl;
  while (true) {
    std::cout << "Работает, ждем соединений" << std::endl;
    User user;
    NetMessage message;
    std::string header = "";
    if (net_server.AcceptConnection(user.user_socket)) {
      if (!NetLibraryServer::ReceiveMessage(user.user_socket, message)) {
        user.user_socket.CloseSocket();
        continue;
      } else {
        header = message.GetHeader();
      }
    } else {
      continue;
    }
    pid_t pid = fork();
    if (pid == 0) {
      switch (SelectQuery(header)) {
      case SENDBLOCKS: {
        ProcessStat(user);
        break;
      }
      case PROCESSSCHEME: {
        ProcessUser(user, message);
        break;
      }
      case NODATA: {
        break;
      }
      }
      break;
      // Тут дочерний процесс выходит из цикла, возвращается в файл
      // main_server.cpp и возвращает 0
    } else {
      continue;
    }
  }
}

QUERY ServerApplication::SelectQuery(const std::string &query) {
  std::cout << "Получил запрос: " << query << std::endl;
  if (query == "BlocksRequest") {
    return SENDBLOCKS;
  } else if (query == "SchemeRequest") {
    return PROCESSSCHEME;
  } else {
    return NODATA;
  }
}

void ServerApplication::ProcessUser(User &user, NetMessage &message) {
  std::cout << "Получил запрос на обработку схемы" << std::endl;
  try {
    std::cout << "Запрос - схема:" << message.GetContent() << std::endl;
    Parser::ParseBlocksFromJsonString(message.GetContent(), user.block_scheme);
    NetLibraryServer::ReceiveMessage(user.user_socket, message);
    std::cout << "Запрос - переменные:" << message.GetContent() << std::endl;
    Parser::ParseParametersFromJsonString(message.GetContent(), user.variables);
    std::string result = machine_factory.ProcessMachine(user);
    NetLibraryServer::SendResultsJson(user.user_socket, result);
  } catch (const std::runtime_error &error) {
    DBHelper::LogData(error.what());
    std::cout << "Не выполнен запрос на обработку схемы. Лог на базу данных "
                 "отправлен."
              << std::endl;
    return;
  }
  DBHelper::LogData("Удачная попытка обработки схемы");
  std::cout << "Выполнен запрос на обработку схемы" << std::endl;
}

void ServerApplication::ProcessStat(User &user) {
  std::cout << "Получил запрос отправку доступных блоков" << std::endl;
  try {
    std::string result = Serializer::ToJsonString(DBHelper::RequestAllBlocks());
    NetLibraryServer::SendBlocksJson(user.user_socket, result);
  } catch (const std::runtime_error &error) {
    DBHelper::LogData(error.what());
    std::cout << "Не выполнен запрос на отправку доступных блоков. Лог на базу "
                 "данных отправлен"
              << std::endl;
    return;
  }
  DBHelper::LogData("Удачная отправка доступных блоков");
  std::cout << "Выполнен запрос на отправку доступных блоков" << std::endl;
}
