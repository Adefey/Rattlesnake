#include <server_application.hpp>

ServerApplication::ServerApplication() {
  db_helper = DBHelper(AppInfo::GetDBAddress(), AppInfo::GetDBUsername(),
                       AppInfo::GetDBPassword(), AppInfo::GetDBDatabase());
}

void ServerApplication::ProcessEvents()
//Точка входа подключений
{}

void ServerApplication::ProcessUser(std::unique_ptr<User> user)
//Обработать запрос на обработку блок-схемы
{}

void ServerApplication::ProcessStat()
//Обработать запрос на сбор статистики
{}
