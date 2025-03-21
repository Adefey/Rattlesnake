// Copyright 2022 Adefe
#include <machine.hpp>

int main(int argc, const char **argv) {
  std::string scheme = argv[1];
  std::string vars = argv[2];
  Machine *machine = new Machine(scheme, vars);
  std::cout << machine->ProcessAllBlocks() << std::endl;
  return EXIT_SUCCESS;
}
