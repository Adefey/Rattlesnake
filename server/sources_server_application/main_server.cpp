// Copyright 2022 Adefe

#include <server_application.hpp>

int main(int argc, char **argv) {
  ServerApplication *application = new ServerApplication;
  application->ProcessEvents();
  return EXIT_SUCCESS;
}
