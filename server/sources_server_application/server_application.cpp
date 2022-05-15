#include <server_application.hpp>

ServerApplication::ServerApplication() {
  db_helper = DBHelper(AppInfo::GetDBAddress(), AppInfo::GetDBUsername(),
                       AppInfo::GetDBPassword(), AppInfo::GetDBDatabase());
  net_server.InitializeServer(8000);
}

void ServerApplication::ProcessEvents() {
  //Точка входа подключений
  std::cout << "Server launched\n" << std::endl;
  std::cout << "Адрес СУБД:" << AppInfo::GetDBAddress() << std::endl;
  std::cout << "Юзер СУБД:" << AppInfo::GetDBUsername() << std::endl;
  std::cout << "Пароль СУБД:" << AppInfo::GetDBPassword() << std::endl;
  std::cout << "База данных СУБД:" << AppInfo::GetDBDatabase() << std::endl;
  std::cout << "Таблица блоков СУБД:" << AppInfo::GetDBBlockTable()
            << std::endl;
  std::cout << "Таблица логов СУБД:" << AppInfo::GetDBLogTable() << std::endl;
  std::cout << "Максимальное число онлайн машин:"
            << AppInfo::GetMaxMachinesCount() << std::endl;
  std::cout << "Интервал обновления:" << AppInfo::GetRefreshPeriod()
            << std::endl;
  while (true) {
    std::cout << "Working..." << std::endl;
    /* //Не трогайте
    User user;
    user.block_scheme = db_helper.RequestAllBlocks();
    user.variables.push_back(Parameter("a", "10"));
    user.variables.push_back(Parameter("b", "20"));
    std::string result = machine_factory.ProcessMachine(user);
    std::cout << result << '\n';
    break;
    */
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
    std::cout << std::endl;
    usleep(AppInfo::GetRefreshPeriod());
  }
}

QUERY ServerApplication::SelectQuery(const std::string &query) {
  if (query == "BlocksRequest") {
    return SENDBLOCKS;
  } else if (query == "SchemeRequest") {
    return PROCESSSCHEME;
  } else {
    return NODATA;
  }
}

void ServerApplication::ProcessUser(User &user, NetMessage &message) {
  Parser::ParseBlocksFromJsonString(message.GetContent(), user.block_scheme);
  NetLibraryServer::ReceiveMessage(user.user_socket, message);
  Parser::ParseParametersFromJsonString(message.GetContent(), user.variables);
  std::string result = machine_factory.ProcessMachine(user);
  NetLibraryServer::SendResultsJson(user.user_socket, result);
}

void ServerApplication::ProcessStat(User &user) {
  std::string result = Serializer::ToJsonString(db_helper.RequestAllBlocks());
  NetLibraryServer::SendBlocksJson(user.user_socket, result);
}
