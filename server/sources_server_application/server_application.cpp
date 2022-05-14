#include <server_application.hpp>

ServerApplication::ServerApplication() {
  db_helper = DBHelper(AppInfo::GetDBAddress(), AppInfo::GetDBUsername(),
                       AppInfo::GetDBPassword(), AppInfo::GetDBDatabase());
  net_server.InitializeServer(8000);
}

void ServerApplication::ProcessEvents() {
  //Точка входа подключений
  std::cout << "Server launched\n" << '\n';
  std::cout << "Адрес СУБД:"<< AppInfo::GetDBAddress() << '\n';
  std::cout << "Юзер СУБД:"<< AppInfo::GetDBUsername() << '\n';
  std::cout << "Пароль СУБД:"<< AppInfo::GetDBPassword() << '\n';
  std::cout << "База данных СУБД:"<< AppInfo::GetDBDatabase() << '\n';
  std::cout << "Таблица блоков СУБД:"<< AppInfo::GetDBBlockTable() << '\n';
  std::cout << "Таблица логов СУБД:"<< AppInfo::GetDBLogTable() << '\n';
  std::cout << "Максимальное число онлайн машин:"<< AppInfo::GetMaxMachinesCount() << '\n';
  std::cout << "Интервал обновления:"<< AppInfo::GetRefreshPeriod() << '\n';
  User user;
  while (true) {
    std::cout << "Working..." << '\n';
    NetMessage message;
    std::string header = "";
    //
    std::vector<Parameter> a = {};
    std::vector<Parameter> b = {};
    user.block_scheme.push_back(Block("./blocks/main.py", a, b, "main.py",
                                      "main example", "adefe", 255));
    user.block_scheme.push_back(Block("./blocks/main2.py", a, b, "main2.py",
                                      "main2 example", "adefe", 155));
    std::string result = machine_factory.ProcessMachine(user);
    std::cout << result;
    break;
    /*
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
    usleep(AppInfo::GetRefreshPeriod());
    */
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
