#include <server_application.hpp>

ServerApplication::ServerApplication()
{}

void ServerApplication::ProcessEvents() //Точка входа подключений
{}
void ServerApplication::ProcessUser(
    std::unique_ptr<User> user) //Обработать запрос на обработку блок-схемы
{}

void ServerApplication::ProcessStat() //Обработать запрос на сбор статистики
{}
